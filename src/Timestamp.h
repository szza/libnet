#pragma once

#include <chrono>


namespace net
{

using std::chrono::system_clock;
using namespace std::literals::chrono_literals;
// 下面这些时间单位，本质都是 duration
using Microsecond = std::chrono::microseconds  ;
using Millisecond = std::chrono::milliseconds  ;
using Second      = std::chrono::seconds       ;
using Minute      = std::chrono::minutes       ;
using Hour        = std::chrono::hours         ;
using Timestamp   = std::chrono::time_point<system_clock>;  // 以 ns 为单位的

namespace clock
{

inline Timestamp now()
{ return  system_clock::now(); }

inline Timestamp nowAfter(Microsecond interval)
{ return now() + interval; }

} // namespce clock

template <typename T>
struct IntervalTypeCheckImpl
{
  static constexpr bool value =
    std::is_same_v<T, Microsecond>  ||
    std::is_same_v<T, Millisecond>  ||
    std::is_same_v<T, Second>       ||
    std::is_same_v<T, Minute>       ||
    std::is_same_v<T, Hour>;
};

#define IntervalTypeCheck(T) \
    static_assert(IntervalTypeCheckImpl<T>::value, "bad interval type")
}
