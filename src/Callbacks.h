#pragma once 

#include <memory>
#include <functional>
#include <string_view>
namespace net
{
using namespace std::string_view_literals;

class TcpConnection;
class InetAddress;
class Buffer;

using TcpConnectionPtr      = std::shared_ptr<TcpConnection>;

using CloseCallback         = std::function<void(const TcpConnectionPtr&)>          ;
using ConnectionCallback    = std::function<void(const TcpConnectionPtr&)>          ;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>          ;  // 这是消息完全发送完毕的回调函数
using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr&, size_t)>  ;  // 这是消息阻塞发不出积累到一定程度时的回调函数
using MessageCallback       = std::function<void(const TcpConnectionPtr&, Buffer&)> ;  // 消息到来的回调函数
using ErrorCallback         = std::function<void()>                                 ;
using NewConnectionCallback = std::function<void(int cfd,const InetAddress& local,
                                                         const InetAddress& peer)>  ;

using Task               = std::function<void()>             ;
using TimerCallback      = std::function<void()>             ;
using ThreadInitCallback = std::function<void(size_t index)> ;

void defaultThreadInitCallback(size_t index);
void defaultConnectionCallback(const TcpConnectionPtr& conn);
void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer& buffer);
}
