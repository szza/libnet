#include <sys/epoll.h>
#include <unistd.h>
#include <assert.h>

#include <src/Logger.h>
#include <src/EventLoop.h>

using namespace net;

EPoller::EPoller(EventLoop* loop)
: loop_(loop),
  epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
  events_(1024)
{
  assert(epollfd_ >0);
}

EPoller::~EPoller()
{
  ::close(epollfd_);
}

void EPoller::poll(ChannelList& activeChannels, int timeout)
{
  loop_->assertInLoopThread();

  int maxEvents = static_cast<int>(events_.size());
  int nEvents = ::epoll_wait(epollfd_, events_.data(), maxEvents, timeout);
  if (nEvents == -1) {
    if (errno != EINTR)
      SYSERR("EPoller::epoll_wait()");
  }
  else if (nEvents > 0) {
    // 填充事件
    for (int i = 0; i < nEvents; ++i) {
      Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
      channel->setRevents(events_[i].events); // 产生的事件
      activeChannels.push_back(channel);      // 加入活跃通道
    }
    if (nEvents == maxEvents)
      events_.resize(2 * events_.size());
  }
}

void EPoller::updateChannel(Channel* channel)
{
  loop_->assertInLoopThread();
  /**
   * polling_ 
   *  false ： ADD
   *  true && 没有关注任何事件 ： MOD
   *  true && 关注了事件，DEL
  */
  int op = 0;
  if (!channel->polling()) {
    assert(!channel->isNoneEvents());
    op = EPOLL_CTL_ADD;
    channel->setPollingState(true);
  }
  else if (!channel->isNoneEvents()) {
    op = EPOLL_CTL_MOD;
  }
  else {
    op = EPOLL_CTL_DEL;
    channel->setPollingState(false);
  }

  updateChannel(op, channel);
}

void EPoller::updateChannel(int op, Channel* channel)
{
  struct epoll_event ee;
  ee.events   = channel->events();
  ee.data.ptr = channel;
  int ret = ::epoll_ctl(epollfd_, op, channel->fd(), &ee);
  if (ret == -1)
    SYSERR("EPoller::epoll_ctl()");
}

