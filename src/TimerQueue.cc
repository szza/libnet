#include <sys/timerfd.h>
#include <strings.h>
#include <unistd.h>
#include <ratio> // std::nano::den

#include <src/Logger.h>
#include <src/EventLoop.h>
#include <src/TimerQueue.h>

using namespace net;

namespace
{

int timerfdCreate()
{
  int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  if (fd == -1)
    SYSFATAL("timer_create()");
  return fd;
}

void timerfdRead(int fd)
{
  uint64_t val;
  ssize_t n = read(fd, &val, sizeof(val));
  if (n != sizeof(val))
    ERROR("timerfdRead get %ld, not %lu", n, sizeof(val));
}

struct timespec durationFromNow(Timestamp when)
{
  struct timespec ret;
  Microsecond ns = std::chrono::duration_cast<Microsecond>((when - clock::now()));
  if (ns < 1ms) ns = 1ms;

  ret.tv_sec = static_cast<time_t>(ns.count() / std::nano::den);
  ret.tv_nsec = (ns.count() % std::nano::den);
  return ret;
}

void timerfdSet(int fd, Timestamp when)
{
  struct itimerspec  newtime;
  bzero(&newtime, sizeof(itimerspec));
  newtime.it_value = durationFromNow(when);

  int ret = timerfd_settime(fd, 0, &newtime, NULL);
  if (ret == -1)
    SYSERR("timerfd_settime()");
}

}

TimerQueue::TimerQueue(EventLoop *loop)
: loop_(loop),
  timerfd_(timerfdCreate()),
  timerChannel_(loop, timerfd_)
{
  loop_->assertInLoopThread();
  timerChannel_.setReadCallback([this]{handleRead();});
  timerChannel_.enableRead();
}

TimerQueue::~TimerQueue()
{
  for (auto& p: timers_)
    delete p.second;
  ::close(timerfd_);
}

Timer* TimerQueue::addTimer(TimerCallback cb, Timestamp when, Microsecond interval)
{
  Timer* timer = new Timer(std::move(cb), when, interval);
  loop_->runInLoop([=]
                  {
                    auto ret = timers_.insert({when, timer});
                    assert(ret.second);
                    // 改变了最早的超时时间，就需要重新设置
                    if (timers_.begin() == ret.first)
                      timerfdSet(timerfd_, when);
                  });
  return timer;
}

void TimerQueue::cancelTimer(Timer* timer)
{
  loop_->runInLoop([timer, this]
                  {
                    timer->cancel();
                    timers_.erase({timer->when(), timer});
                    delete timer;
                  });
}

void TimerQueue::handleRead()
{
  loop_->assertInLoopThread();
  timerfdRead(timerfd_);

  Timestamp now(clock::now());
  
  // 处理超时事件
  for (auto& e: getExpired(now)) {
    Timer* timer = e.second;
    assert(timer->expired(now));

    if (!timer->canceled())
      timer->run();
    
    // 如果设置为重复模式，重新插入
    if (!timer->canceled() && timer->repeat()) 
    {
      timer->restart();
      e.first = timer->when();
      timers_.insert(e);  
    }
    else
    {
      delete timer;
    } 
  }

  if (!timers_.empty())
    timerfdSet(timerfd_, timers_.begin()->first);
}

std::vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now)
{
    Entry en(now + 1ns, nullptr);
    std::vector<Entry> entries;

    auto end = timers_.lower_bound(en);
    entries.assign(timers_.begin(), end);
    timers_.erase(timers_.begin(), end);

    return entries;
}

