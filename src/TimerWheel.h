#pragma once 

#include <src/TcpConnection.h>
#include <src/Timestamp.h>
#include <src/EventLoop.h>
#include <src/Logger.h>

#include <unordered_set>
#include <memory>
#include <vector>

namespace net { 

struct ConnectionEntry : public std::enable_shared_from_this<ConnectionEntry> {
  
  ConnectionEntry(const TcpConnectionPtr& connptr)
  :w_connptr(connptr) 
  { }

  ~ConnectionEntry() 
  {
    auto connptr = w_connptr.lock();
    if(connptr) 
    { 
      INFO("connection %s is disconnected in time",
          connptr->name().c_str());

      connptr->forceClose();
    }
  }

private:
  std::weak_ptr<TcpConnection> w_connptr;
};

class TimeWheel { 
public:
  TimeWheel(EventLoop* loop, Microsecond expiration=10s)
  : loop_(loop),
    index_(0),
    expired_(std::chrono::duration_cast<Second>(expiration).count())
  {
  }
  
  ~TimeWheel()=default;

  void start() { 
    if(this->expired_ <= 0)
      return;

    wheels_.resize(expired_);
    loop_->runEvery(1s, 
                    [this]
                    { 
                      if(this->expired_<= 0)
                        return;
                      if(++index_ == expired_) 
                      { 
                        index_ =0;
                      }

                      wheels_[index_].clear();
                    });
  }

  void insert(const TcpConnectionPtr& connptr) { 
    if(this->expired_ <= 0)
      return;

    if(connptr) 
    {
      wheels_[index_].emplace(std::make_shared<ConnectionEntry>(connptr));
    }
  }

  void setExpiration(Microsecond expiration) { expired_ = std::chrono::duration_cast<Second>(expiration).count(); }
private:
  using EntrypPtr = std::shared_ptr<ConnectionEntry>;
  
  template<typename T>
  using TimerList = std::vector<std::unordered_set<T>>;

  EventLoop*            loop_;
  int64_t               index_;
  int64_t               expired_; // 超时时间
  TimerList<EntrypPtr>  wheels_;
};


}; // namespace net