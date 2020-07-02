#pragma once 

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

#include <sys/types.h>

#include <src/Timer.h>
#include <src/EPoller.h>
#include <src/TimerQueue.h>

namespace net
{

class EventLoop: noncopyable
{
public:
  EventLoop();
  ~EventLoop();

  void loop();
  void quit(); 

  void runInLoop(const Task& task);
  void runInLoop(Task&& task);
  void queueInLoop(const Task& task);
  void queueInLoop(Task&& task);

  Timer* runAt(Timestamp when,          TimerCallback callback);
  Timer* runAfter(Microsecond interval, TimerCallback callback);
  Timer* runEvery(Microsecond interval, TimerCallback callback);
  void   cancelTimer(Timer* timer);

  void wakeup();

  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);

  void assertInLoopThread();
  void assertNotInLoopThread();
  bool isInLoopThread();

private:
  void doPendingTasks();
  void handleRead();
  int  getNextTimeout() { 
    if(!pendingTasks_.empty()) { 
      return 0;
    } 
    // 获取最早的超时时间
    return static_cast<int>(timerQueue_->nextTimeout());
  }

  using ChannelList = std::vector<Channel*>;
  using TaskList    = std::vector<Task>;

  std::thread::id               tid_;
  std::atomic<bool>             quit_;
  bool                          doingPendingTasks_;
  int                           wakeupFd_;
  std::unique_ptr<EPoller>      poller_;
  std::unique_ptr<Channel>      wakeupChannel_;
  ChannelList                   activeChannels_;
  TaskList                      pendingTasks_;
  std::mutex                    mutex_;
  std::unique_ptr<TimerQueue>   timerQueue_;
};

}