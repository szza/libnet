#pragma once

#include <assert.h>

#include <src/Callbacks.h>
#include <src/Timestamp.h>
#include <src/Channel.h>

namespace net
{

class Timer: noncopyable
{
public:
  Timer(TimerCallback callback, Timestamp when, Microsecond interval)
  : callback_(std::move(callback)),
    when_(when),
    interval_(interval),
    repeat_(interval_ > Microsecond::zero()),
    canceled_(false)
  { }

  bool      expired(Timestamp now) const { return now >= when_; }
  bool      repeat()               const { return repeat_;      }
  Timestamp when()                 const { return when_;        }
  bool      canceled()             const { return canceled_;    }

  void run() 
  { 
    if (callback_) 
      callback_(); 
  }

  void restart()
  {
    assert(repeat_);
    when_ += interval_;
  }

  void cancel()
  {
    assert(!canceled_);
    canceled_ = true;
  }

private:
  TimerCallback callback_;
  Timestamp     when_;
  Microsecond   interval_;
  bool          repeat_;
  bool          canceled_;
};

}