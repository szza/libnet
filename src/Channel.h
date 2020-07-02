#pragma once 

#include <functional>
#include <memory>

#include <sys/epoll.h>

#include <src/noncopyable.h>

namespace net
{

class EventLoop;

class Channel: noncopyable {
public:
  using ReadCallback  = std::function<void()> ;
  using WriteCallback = std::function<void()> ;
  using CloseCallback = std::function<void()> ;
  using ErrorCallback = std::function<void()> ;

  Channel(EventLoop* loop, int fd);
  ~Channel();

  void setReadCallback (const ReadCallback& cb) { readCallback_  = cb; }
  void setWriteCallback(const WriteCallback& cb){ writeCallback_ = cb; }
  void setCloseCallback(const CloseCallback& cb){ closeCallback_ = cb; }
  void setErrorCallback(const ErrorCallback& cb){ errorCallback_ = cb; }

  void setRevents(uint32_t revents) { revents_ = revents; }
  void setPollingState(bool state)  { polling_ = state;   }

  int      fd()           const { return fd_;                }
  uint32_t events()       const { return events_;            }
  bool     polling()      const { return polling_;           }
  bool     isNoneEvents() const { return events_ == 0;       }
  bool     isReading()    const { return events_ & EPOLLIN;  }
  bool     isWriting()    const { return events_ & EPOLLOUT; }

  void enableRead()  { events_ |= EPOLLIN | EPOLLPRI;  update();}
  void enableWrite() { events_ |= EPOLLOUT;            update();}
  void disableRead() { events_ &= ~EPOLLIN;            update();}
  void disableWrite(){ events_ &= ~EPOLLOUT;           update();}
  void disableAll()  { events_ = 0;                    update();}

  void remove();
  void tie(const std::shared_ptr<void>& obj);
  void handleEvents();
private:
  void update();
  void handleEventsWithGuard();

  bool                polling_;
  bool                tied_;
  bool                handlingEvents_; 
  int                 fd_;
  uint32_t            events_;          // 关注的事件
  uint32_t            revents_;         // 产生的事件
  EventLoop*          loop_;
  std::weak_ptr<void> tie_;             // 延长TcpConnection的生命周期
  ReadCallback        readCallback_;
  WriteCallback       writeCallback_;
  CloseCallback       closeCallback_;
  ErrorCallback       errorCallback_;
};

}
