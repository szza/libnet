#include <assert.h>
#include <sys/eventfd.h>
#include <sys/types.h> // pid_t
#include <unistd.h>	   // syscall()
#include <syscall.h>   // SYS_gettid
#include <signal.h>
#include <numeric>

#include "Logger.h"
#include "Channel.h"
#include "EventLoop.h"

using namespace net;

namespace
{

thread_local EventLoop* t_Eventloop = nullptr;

class IgnoreSigPipe
{
public:
  IgnoreSigPipe()
  {
    ::signal(SIGPIPE, SIG_IGN);
  }
};

IgnoreSigPipe ignore;

} // unnamed-namespace

EventLoop::EventLoop()
: tid_(std::this_thread::get_id()),
  quit_(false),
  doingPendingTasks_(false),
  wakeupFd_(::eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK)),
  poller_(std::make_unique<EPoller>(this)),
  wakeupChannel_(std::make_unique<Channel>(this, wakeupFd_)),
  timerQueue_(std::make_unique<TimerQueue>(this))
{
  assert(wakeupFd_ >0 && "EventLoop::eventfd() fail to create.");
  // 因为是为了唤醒eventLoop，因此必须存在可读事件
  wakeupChannel_->setReadCallback([this]{handleRead();});
  wakeupChannel_->enableRead();

  assert(t_Eventloop == nullptr && "EventLoop has been created.");
  t_Eventloop = this;
}

EventLoop::~EventLoop()
{
  assert(t_Eventloop == this);
  t_Eventloop = nullptr;
}

void EventLoop::loop()
{
  assertInLoopThread();
  quit_ = false;
  while (!quit_) {
    activeChannels_.clear();
    int timeout = getNextTimeout();
    poller_->poll(activeChannels_, timeout);
    for (auto channel: activeChannels_)
        channel->handleEvents();
    doPendingTasks();
  }
}

void EventLoop::quit()
{
  assert(!quit_);
  quit_ = true;
  if (!isInLoopThread())
      wakeup();
}

void EventLoop::runInLoop(const Task& task)
{
  if (isInLoopThread())
  {
    task();
  } 
  else
  {
    queueInLoop(task);
  }
}

void EventLoop::runInLoop(Task&& task)
{
  if (isInLoopThread())
  {
    task();
  }
  else
  {
    queueInLoop(std::move(task));
  }
}

/** @brief: 这个函数是暴露给外部， 对于任务队列  @b pendingTasks_, 
 *  其他线程向里面添加任务。当前线程要从里面取出任务，
 *  因此，会存在 race condition，所以需要加锁
 * */
void EventLoop::queueInLoop(const Task& task)
{
  {
    std::lock_guard<std::mutex> guard(mutex_);
    pendingTasks_.push_back(task);
  }
  if (!isInLoopThread() || doingPendingTasks_)
    wakeup();
}

void EventLoop::queueInLoop(Task&& task)
{
  {
    std::lock_guard<std::mutex> guard(mutex_);
    pendingTasks_.push_back(std::move(task));
  }
  if (!isInLoopThread() || doingPendingTasks_)
    wakeup();
}

Timer* EventLoop::runAt(Timestamp when, TimerCallback callback)
{
  return timerQueue_->addTimer(std::move(callback), when, Millisecond::zero());
}

Timer* EventLoop::runAfter(Microsecond interval, TimerCallback callback)
{
  return runAt(clock::now() + interval, std::move(callback));
}

Timer* EventLoop::runEvery(Microsecond interval, TimerCallback callback)
{
  return timerQueue_->addTimer(std::move(callback),
                               clock::now() + interval,
                               interval);
}

void EventLoop::cancelTimer(Timer* timer)
{
    timerQueue_->cancelTimer(timer);
}


void EventLoop::wakeup()
{
  uint64_t one = 1;
  ssize_t n = ::write(wakeupFd_, &one, sizeof(one));
  if (n != sizeof(one))
      SYSERR("EventLoop::wakeup() should ::write() %lu bytes", sizeof(one));
}


void EventLoop::updateChannel(Channel* channel)
{
  assertInLoopThread();
  poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
  assertInLoopThread();
  channel->disableAll();
}

void EventLoop::assertInLoopThread()
{
  assert(isInLoopThread());
}

void EventLoop::assertNotInLoopThread()
{
  assert(!isInLoopThread());
}

bool EventLoop::isInLoopThread()
{
  return tid_ == std::this_thread::get_id();
}

void EventLoop::doPendingTasks()
{
  assertInLoopThread();
  // 使用局部变量，来减少锁的阻塞时间
  std::vector<Task> tasks;
  {
    std::lock_guard<std::mutex> guard(mutex_);
    tasks.swap(pendingTasks_);
  }

  doingPendingTasks_ = true;
  for (Task& task: tasks)
  {
    task();
  }
  doingPendingTasks_ = false;
}

void EventLoop::handleRead()
{
  uint64_t one;
  ssize_t n = ::read(wakeupFd_, &one, sizeof(one));
  if (n != sizeof(one))
    SYSERR("EventLoop::handleRead() should ::read() %lu bytes", sizeof(one));
}