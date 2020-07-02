#pragma once 

#include <src/InetAddress.h>
#include <src/noncopyable.h>
#include <src/Callbacks.h>
#include <src/Channel.h>
#include <src/Buffer.h>

#include <string_view>
#include <string>
#include <atomic>

namespace net
{

class EventLoop;

class TcpConnection: noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
  TcpConnection(EventLoop* loop, 
                int sockfd,
                const InetAddress& local,
                const InetAddress& peer);
  ~TcpConnection();

  void setMessageCallback(const MessageCallback& cb)                          { messageCallback_ = cb;       }
  void setWriteCompleteCallback(const WriteCompleteCallback& cb)              { writeCompleteCallback_ = cb; }
  void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t mark) { highWaterMarkCallback_ = cb; highWaterMark_ = mark; }
  void setCloseCallBack(const CloseCallback& cb)                              { closeCallback_ = cb; }

  void setMessageCallback(MessageCallback&& cb)                          { messageCallback_ = std::move(cb);       }
  void setWriteCompleteCallback(WriteCompleteCallback&& cb)              { writeCompleteCallback_ = std::move(cb); }
  void setHighWaterMarkCallback(HighWaterMarkCallback&& cb, size_t mark) { highWaterMarkCallback_ = std::move(cb); highWaterMark_ = mark; }
  void setCloseCallBack(CloseCallback&& cb)                              { closeCallback_ = std::move(cb); }

  void connectEstablished();
  bool connected()    const;
  bool disconnected() const;

  const InetAddress& local() const { return *local_; }
  const InetAddress& peer()  const { return *peer_; }
  std::string name()         const { return peer_->toIpPort() + " -> " + local_->toIpPort(); }

  void send(std::string_view data);
  void send(const char* data, size_t len);
  void send(Buffer& buffer);
  void shutdown();
  void forceClose();

  void stopRead();
  void startRead();
  bool isReading() // not thread safe
  { return channel_->isReading(); };

  const Buffer& inputBuffer()  const { return *inputBuffer_; }
  const Buffer& outputBuffer() const { return *outputBuffer_; }

private:
  enum State { kConnecting, kConnected, kDisconnecting, kDisconnected};

  void handleRead();
  void handleWrite();
  void handleClose();
  void handleError();

  void sendInLoop(const char* data, size_t len);
  void sendInLoop(const std::string& message);
  void shutdownInLoop();
  void forceCloseInLoop();

  EventLoop*                    loop_;
  std::atomic<int>              state_;
  int                           cfd_;
  std::unique_ptr<Channel>      channel_;
  std::unique_ptr<InetAddress>  local_;
  std::unique_ptr<InetAddress>  peer_;
  std::unique_ptr<Buffer>       inputBuffer_;
  std::unique_ptr<Buffer>       outputBuffer_;

  MessageCallback          messageCallback_;
  CloseCallback            closeCallback_;
  WriteCompleteCallback    writeCompleteCallback_;
  HighWaterMarkCallback    highWaterMarkCallback_;
  size_t                   highWaterMark_;
};

}
