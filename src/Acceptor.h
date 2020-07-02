#pragma once

#include <memory>

#include <src/noncopyable.h>
#include <src/InetAddress.h>
#include <src/Channel.h>

namespace net
{

class EventLoop;

class Acceptor:noncopyable
{
public:
  Acceptor(EventLoop* loop, const InetAddress& local);
  ~Acceptor();

  void listen();  
  
  bool listening() const { return listening_; }
  
  void setNewConnectionCallback(const NewConnectionCallback& cb) 
  { newConnectionCallback_ = cb; }
private:
  void handleRead(); 
  
  bool                      listening_;
  int                       listenFd_;
  int                       emfileFd_;
  EventLoop*                loop_;
  std::unique_ptr<Channel>  listenChannle_;  
  InetAddress               local_;
  NewConnectionCallback     newConnectionCallback_;
};

}