#pragma once 

#include <condition_variable>
#include <atomic>
#include <vector>
#include <thread>
#include <mutex>

#include <src/TcpServerSingle.h>
#include <src/noncopyable.h>
#include <src/InetAddress.h>
#include <src/Callbacks.h>

namespace net
{

class EventLoopThread;
class TcpServerSingle;
class EventLoop;
class InetAddress;

class TcpServer: noncopyable
{
public:
  TcpServer(EventLoop* loop, const InetAddress& local);
  ~TcpServer();
  // n == 0 || n == 1: all things run in baseLoop thread
  // n > 1: set another (n - 1) eventLoop threads.
  void setNumThread(size_t n);
  // set all threads begin to loop and accept new connections
  // except the baseLoop thread
  void start();

  void setThreadInitCallback(const ThreadInitCallback& cb)        { threadInitCallback_ = cb;    }
  void setConnectionCallback(const ConnectionCallback& cb)        { connectionCallback_ = cb;    }
  void setMessageCallback(const MessageCallback& cb)              { messageCallback_ = cb;       }
  void setWriteCompleteCallback(const WriteCompleteCallback& cb)  { writeCompleteCallback_ = cb; }
private:
  void startInLoop();
  void runInThread(size_t index);

  using ThreadPtr          = std::unique_ptr<std::thread> ;
  using ThreadPtrList      = std::vector<ThreadPtr>;
  using TcpServerSinglePtr = std::unique_ptr<TcpServerSingle>;
  using EventLoopList      = std::vector<EventLoop*>;

  EventLoop*              baseLoop_;
  TcpServerSinglePtr      baseServer_;
  ThreadPtrList           threads_;
  EventLoopList           eventLoops_;
  size_t                  numThreads_;
  std::atomic<bool>       started_;
  InetAddress             local_;
  std::mutex              mutex_;
  std::condition_variable cond_;
  ThreadInitCallback      threadInitCallback_;
  ConnectionCallback      connectionCallback_;
  MessageCallback         messageCallback_;
  WriteCompleteCallback   writeCompleteCallback_;
};

}