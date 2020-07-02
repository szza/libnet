#pragma once 

#include <vector>

#include <src/noncopyable.h>

namespace net
{

class EventLoop;
class Channel;

class EPoller: noncopyable
{
public:
  using ChannelList = std::vector<Channel*>;
  using EventList   = std::vector<struct epoll_event>;

  explicit
  EPoller(EventLoop* loop);
  ~EPoller();

  void poll(ChannelList& activeChannels,int timeout=-1);
  void updateChannel(Channel* channel);

private:
  void updateChannel(int op, Channel* channel);

  EventLoop* loop_;
  int        epollfd_;
  EventList  events_; // 产生的事件
};
}