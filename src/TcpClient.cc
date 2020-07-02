#include <src/Logger.h>
#include <src/EventLoop.h>
#include <src/TcpConnection.h>
#include <src/TcpClient.h>

using namespace net;

TcpClient::TcpClient(EventLoop* loop, const InetAddress& peer)
: loop_(loop),
  connected_(false),
  peer_(peer),
  retryTimer_(nullptr),
  connector_(new Connector(loop, peer)),
  connectionCallback_(defaultConnectionCallback),
  messageCallback_(defaultMessageCallback)
{
  connector_->setNewConnectionCallback([this](auto connfd, auto loc, auto p)
                                      { 
                                        this->newConnection(connfd, loc, p);
                                      });
}

TcpClient::~TcpClient()
{
    if (connection_ && !connection_->disconnected())
        connection_->forceClose();
    if (retryTimer_ != nullptr) {
        loop_->cancelTimer(retryTimer_);
    }
}

void TcpClient::start()
{
    loop_->assertInLoopThread();
    connector_->start();
    retryTimer_ = loop_->runEvery(3s, [this](){ retry(); });
}

void TcpClient::retry()
{
    loop_->assertInLoopThread();
    if (connected_) {
        return;
    }

    WARN("TcpClient::retry() reconnect %s...", peer_.toIpPort().c_str());
    connector_ = std::make_unique<Connector>(loop_, peer_);
    connector_->setNewConnectionCallback([this](auto connfd, auto local, auto peer)
                                        { 
                                          this->newConnection(connfd, local, peer);
                                        });    
    connector_->start();
}

void TcpClient::newConnection(int connfd, const InetAddress& local, const InetAddress& peer)
{
    loop_->assertInLoopThread();
    loop_->cancelTimer(retryTimer_);
    retryTimer_ = nullptr; // avoid duplicate cancel
    connected_ = true;
    auto conn = std::make_shared<TcpConnection>
            (loop_, connfd, local, peer);
    connection_ = conn;
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallBack([this](auto connptr) 
                          { 
                            this->closeConnection(connptr);
                          });
    conn->connectEstablished();
    connectionCallback_(conn);
}

void TcpClient::closeConnection(const TcpConnectionPtr& conn)
{
    loop_->assertInLoopThread();
    assert(connection_ != nullptr);
    connection_.reset();
    connectionCallback_(conn);
}