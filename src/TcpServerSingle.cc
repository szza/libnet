
#include "TcpServerSingle.h"
#include "TcpConnection.h"
#include "EventLoop.h"

using namespace net;

TcpServerSingle::TcpServerSingle(EventLoop* loop, const InetAddress& local)
: loop_(loop),
  acceptor_(std::make_unique<Acceptor>(loop, local)),
  timewheel_(std::make_unique<TimeWheel>(loop))
{
  acceptor_->setNewConnectionCallback([this](auto connfd, auto loc, auto peer)
                                      { 
                                        this->newConnection(connfd, loc, peer);
                                      });
}

void TcpServerSingle::start()
{
  acceptor_->listen();
  timewheel_->start();
}

void TcpServerSingle::newConnection(int connfd,
                                    const InetAddress& local,
                                    const InetAddress& peer)
{
  loop_->assertInLoopThread();
  auto connPtr = std::make_shared<TcpConnection>(loop_, connfd, local, peer);
  connections_.insert(connPtr);

  connPtr->setMessageCallback(messageCallback_);
  connPtr->setWriteCompleteCallback(writeCompleteCallback_);
  connPtr->setCloseCallBack([this](const TcpConnectionPtr& connptr)
                            {
                              this->closeConnection(connptr);
                            });

  connPtr->connectEstablished();
  timewheel_->insert(connPtr);
  connectionCallback_(connPtr); 
}

void TcpServerSingle::closeConnection(const TcpConnectionPtr& connPtr)
{
  loop_->assertInLoopThread();
  size_t ret = connections_.erase(connPtr);
  assert(ret == 1);(void)ret;
}

