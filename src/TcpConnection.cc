#include <assert.h>
#include <unistd.h>

#include <src/Logger.h>
#include <src/EventLoop.h>
#include <src/TcpConnection.h>

using namespace net;

namespace net
{

void defaultThreadInitCallback(size_t index)
{
    TRACE("EventLoop thread #%lu started", index);
}

void defaultConnectionCallback(const TcpConnectionPtr& conn)
{
    INFO("connection %s -> %s %s",
          conn->peer().toIpPort().c_str(),
          conn->local().toIpPort().c_str(),
          conn->connected() ? "up" : "down");
}

void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer& buffer)
{
    TRACE("connection %s -> %s recv %lu bytes",
          conn->peer().toIpPort().c_str(),
          conn->local().toIpPort().c_str(),
          buffer.readableBytes());
    buffer.retrieveAll();
}

} // namespace -end

TcpConnection::TcpConnection(EventLoop *loop, 
                             int cfd,
                             const InetAddress& local,
                             const InetAddress& peer)
: loop_(loop),
  state_(kConnecting), // 当创建 TcpConnection 对象时，说明有连接请求了
  cfd_(cfd),
  channel_(std::make_unique<Channel>(loop, cfd_)),
  local_(std::make_unique<InetAddress>(local)),
  peer_(std::make_unique<InetAddress>(peer)),
  inputBuffer_(std::make_unique<Buffer>()),
  outputBuffer_(std::make_unique<Buffer>()),
  highWaterMark_(0)
{
  channel_->setReadCallback ([this]{this->handleRead();});
  channel_->setWriteCallback([this]{this->handleWrite();});
  channel_->setCloseCallback([this]{this->handleClose();});
  channel_->setErrorCallback([this]{this->handleError();});

  TRACE("TcpConnection() %s fd=%d", name().c_str(), cfd);
}

TcpConnection::~TcpConnection()
{
  // if(state_ != kDisconnected) { 
  //   handleClose();
  // }
  assert(state_ == kDisconnected);
  ::close(cfd_);

  TRACE("~TcpConnection() %s fd=%d", name().c_str(), cfd_);
}

void TcpConnection::connectEstablished()
{
    assert(state_ == kConnecting);
    state_ = kConnected;
    channel_->tie(shared_from_this());
    channel_->enableRead();
}

bool TcpConnection::connected() const
{ return state_ == kConnected; }

bool TcpConnection::disconnected() const
{ return state_ == kDisconnected; }

void TcpConnection::send(std::string_view data)
{
  send(data.data(), data.length());
}

// 线程安全的发送
void TcpConnection::send(const char *data, size_t len)
{
  if (state_ != kConnected) {
    WARN("TcpConnection::send() not connected, give up send");
    return;
  }

  if (loop_->isInLoopThread()) 
  {
    sendInLoop(data, len);
  }
  else 
  {
    loop_->queueInLoop([this, str = std::string(data, data+len)]
                        { 
                          this->sendInLoop(str);
                        });
  }
}

void TcpConnection::sendInLoop(const char *data, size_t len) {
  loop_->assertInLoopThread();
  if (state_ == kDisconnected) {
    WARN("TcpConnection::sendInLoop() disconnected, give up send");
    return;
  }

  ssize_t n = 0;
  size_t remain = len;
  bool faultError = false;

  /// @brief: 如果没有注册可写事件，输出缓冲区中没有数据，则直接发
  if (!channel_->isWriting() && outputBuffer_->readableBytes() == 0) {
    n = ::write(cfd_, data, len);
    if (n == -1) 
    {
      if (errno != EWOULDBLOCK || errno != EINTR) {
        SYSERR("TcpConnection::write()");
        if (errno == EPIPE || errno == ECONNRESET)
          faultError = true;
      }
      n = 0;
    }
    else 
    {
      remain -= static_cast<size_t>(n);
      if (remain == 0 && writeCompleteCallback_) {
        loop_->queueInLoop([this]
                          { 
                            this->writeCompleteCallback_(this->shared_from_this()); 
                          });
      }
    }
  }

  if (!faultError && remain > 0) {
    if (highWaterMarkCallback_) {
      size_t oldLen = outputBuffer_->readableBytes();
      size_t newLen = oldLen + remain;
      if (oldLen < highWaterMark_ && newLen >= highWaterMark_)
        loop_->queueInLoop([this, &newLen] 
                           { 
                            this->highWaterMarkCallback_(this->shared_from_this(), 
                                                         newLen); 
                           });
    }
    /// 将剩余内容，添加到 outputBuffer_
    outputBuffer_->append(data + n, remain);

    if(!channel_->isWriting()) 
    { 
      channel_->enableWrite();
    }
  }
}

void TcpConnection::sendInLoop(const std::string& message)
{
    sendInLoop(message.data(), message.size());
}

void TcpConnection::send(Buffer& buffer)
{
    if (state_ != kConnected) {
        WARN("TcpConnection::send() not connected, give up send");
        return;
    }

    if (loop_->isInLoopThread()) 
    {
      sendInLoop(buffer.peek(), buffer.readableBytes());
      buffer.retrieveAll();
    }
    else 
    {
      loop_->queueInLoop([this, str = buffer.retrieveAllAsString()]
                        { 
                          this->sendInLoop(str); 
                        });
    }
}

void TcpConnection::shutdown()
{
  assert(state_ <= kDisconnecting);
  if (state_.exchange(kDisconnecting) ==kConnected) {
    if (loop_->isInLoopThread())
    {
      shutdownInLoop();
    }
    else 
    {
      loop_->queueInLoop([this]
                         { 
                          this->shutdownInLoop();
                         });
    }
  }
}

void TcpConnection::shutdownInLoop()
{
  loop_->assertInLoopThread();
  // 要等待发送数据都已经发送完毕，再执行shutdown，即看是否 还关注了可写事件
  if (state_ != kDisconnected && !channel_->isWriting()) {
      if (::shutdown(cfd_, SHUT_WR) == -1)
          SYSERR("TcpConnection:shutdown()");
  }
}

void TcpConnection::forceClose()
{
  // 为什么要先判断下，因为可能之前这个连接就关闭了
  // 然后又再关闭一次，forceCloseInLoop 是不会执行的，而是直接进入析构函数
  // 此时，对象已经关闭了，但是状态已经被改为 kDisconnecting  析构函数中的 assert 会触发
  if (state_ != kDisconnected && state_.exchange(kDisconnecting) != kDisconnected) {
    loop_->queueInLoop([this]
                       { 
                        this->forceCloseInLoop();
                       });
  }
}

void TcpConnection::forceCloseInLoop()
{
  loop_->assertInLoopThread();
  if (state_ != kDisconnected) {
      handleClose();
  }
}

void TcpConnection::stopRead()
{
  loop_->runInLoop([this]
                   {
                      if (channel_->isReading())
                      {
                        channel_->disableRead();
                      }
                   });
}

void TcpConnection::startRead()
{
    loop_->runInLoop([this]
                      {
                       if (!channel_->isReading())
                       {
                        channel_->enableRead();
                       }
                      });
}

void TcpConnection::handleRead()
{
    loop_->assertInLoopThread();
    assert(state_ != kDisconnected);
    int savedErrno;
    ssize_t n = inputBuffer_->readFd(cfd_, &savedErrno);
    if (n == -1) 
    {
      errno = savedErrno;
      SYSERR("TcpConnection::read()");
      handleError();
    }
    else if (n == 0)
    {
      handleClose();
    }
    else 
    {
      messageCallback_(shared_from_this(), *inputBuffer_);
    }
}

void TcpConnection::handleWrite()
{
  if (state_ == kDisconnected) 
  {
    WARN("TcpConnection::handleWrite() disconnected, "
          "give up writing %lu bytes", outputBuffer_->readableBytes());
    return;
  }

  assert(outputBuffer_->readableBytes() > 0);
  assert(channel_->isWriting());
  ssize_t n = ::write(cfd_, outputBuffer_->peek(), outputBuffer_->readableBytes());
  if (n == -1) 
  {
    SYSERR("TcpConnection::write()");
  }
  else 
  {
    outputBuffer_->retrieve(static_cast<size_t>(n));
    if (outputBuffer_->readableBytes() == 0) {
      channel_->disableWrite();
      if (writeCompleteCallback_) 
      {
        loop_->queueInLoop([this]
                           { 
                             this->writeCompleteCallback_(this->shared_from_this());
                           });
      }

      if (state_ == kDisconnecting) 
      {
        shutdownInLoop();
      }
    }
  }
}

void TcpConnection::handleClose()
{
    loop_->assertInLoopThread();
    assert(state_ == kConnected || state_ == kDisconnecting);
    state_ = kDisconnected;
    loop_->removeChannel(channel_.get());
    closeCallback_(this->shared_from_this());
}

void TcpConnection::handleError()
{
    int err;
    socklen_t len = sizeof(err);
    int ret = getsockopt(cfd_, SOL_SOCKET, SO_ERROR, &err, &len);
    if (ret != -1)
        errno = err;
    SYSERR("TcpConnection::handleError()");
}
