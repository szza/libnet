#pragma once 

#include <src/Callbacks.h>
#include <src/Connector.h>
#include <src/Timer.h>

namespace net
{

class TcpClient: noncopyable
{
public:
    TcpClient(EventLoop* loop, const InetAddress& peer);
    ~TcpClient();

    void start();
    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }
    void setErrorCallback(const ErrorCallback& cb)
    { connector_->setErrorCallback(cb); }

private:
    void retry();
    void newConnection(int connfd, const InetAddress& local, const InetAddress& peer);
    void closeConnection(const TcpConnectionPtr& conn);

    using ConnectorPtr = std::unique_ptr<Connector>;

    EventLoop*            loop_;
    bool                  connected_;
    InetAddress           peer_;
    Timer*                retryTimer_;
    ConnectorPtr          connector_;
    TcpConnectionPtr      connection_;
    ConnectionCallback    connectionCallback_;
    MessageCallback       messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
};

}
