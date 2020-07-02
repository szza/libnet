#pragma once 

#include <thread>

#include <src/CountDownLatch.h>

namespace net
{

class EventLoop;

class EventLoopThread: noncopyable
{
public:
  EventLoopThread();
  ~EventLoopThread();

  EventLoop* startLoop();

private:
  void runInThread();

  bool           started_ ;
  EventLoop*     loop_ ;
  std::thread    thread_;
  CountDownLatch latch_;
};

}