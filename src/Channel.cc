#include <assert.h>

#include <src/EventLoop.h>
#include <src/Channel.h>

using namespace net;

Channel::Channel(EventLoop* loop, int fd)
: polling_(false),
  tied_(false),
  handlingEvents_(false),
  fd_(fd),
  events_(0),
  revents_(0),
  loop_(loop),
  readCallback_(nullptr),
  writeCallback_(nullptr),
  closeCallback_(nullptr),
  errorCallback_(nullptr)
{ }

Channel::~Channel()
{ assert(!handlingEvents_); }

void Channel::handleEvents()
{
  loop_->assertInLoopThread();
  // 处理事件
  if (tied_) 
  {
    auto guard = tie_.lock();
    /// 这个 @b guard 作用
    /// 1 查看 TcpConnection 对象是否存在
    /// 2 如果 TcpConnection 对象还没有断开连接，那么这个 guard 可以保证在处理事件过程中不会被释放
    ///   延长其生命周期
    if (guard != nullptr)
      handleEventsWithGuard();
  }
  else
  {
    // 这里实际上不会执行
    handleEventsWithGuard();
  } 
}

void Channel::handleEventsWithGuard()
{
  handlingEvents_ = true;

  if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
    if (closeCallback_) 
      closeCallback_();
  }
  if (revents_ & EPOLLERR) {
    if (errorCallback_) 
      errorCallback_();
  }
  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    if (readCallback_) 
      readCallback_();
  }
  if (revents_ & EPOLLOUT) {
    if (writeCallback_) 
      writeCallback_();
  }

  handlingEvents_ = false;
}

void Channel::tie(const std::shared_ptr<void>& obj)
{
  tie_ = obj;
  tied_ = true;
}

void Channel::update()
{
  loop_->updateChannel(this);
}

void Channel::remove()
{
  assert(polling_);
  loop_->removeChannel(this);
}
