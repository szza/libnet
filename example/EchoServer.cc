#include <map>

#include <src/TcpConnection.h>
#include <src/EventLoop.h>
#include <src/TcpServer.h>
#include <src/Logger.h>

#include <iostream>
#include <signal.h>

using namespace net;

class EchoServer
{
public:
  EchoServer(EventLoop* loop, const InetAddress& addr, size_t numThread = 1, Microsecond timeout = 5s)
  : loop_(loop),
    server_(loop, addr),
    numThread_(numThread),
    timeout_(timeout)
  {
    server_.setConnectionCallback([this](const auto& connptr)
                                  { 
                                    this->onConnection(connptr);
                                  });
    server_.setMessageCallback([this](const auto& connptr, auto& buffer) 
                               { 
                                this->onMessage(connptr, buffer); 
                               });
    server_.setWriteCompleteCallback([this](const auto& connptr)
                                     { 
                                       this->onWriteComplete(connptr);
                                     });
  }

  ~EchoServer()
  {  }

  void start()
  {
    // set thread num here
    server_.setNumThread(numThread_);
    server_.start();
  }

  void onConnection(const TcpConnectionPtr& conn)
  {
    INFO("connection %s is [%s]",
          conn->name().c_str(),
          conn->connected() ? "up":"down");

    if (conn->connected()) 
    {
      conn->setHighWaterMarkCallback([this](const auto& connptr, const auto& mark)
                                      {
                                        this->onHighWaterMark(connptr, mark);
                                      },
                                      1024);
    }
    else 
    { 
      connections_.erase(conn);
    }
  }

  void onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
  {
    TRACE("connection %s recv %lu bytes",
          conn->name().c_str(),
          buffer.readableBytes());

    conn->send(buffer);
  }

  void onHighWaterMark(const TcpConnectionPtr& conn, size_t mark)
  {
    INFO("high water mark %lu bytes, stop read", mark);
    conn->stopRead();
  }

  void onWriteComplete(const TcpConnectionPtr& conn)
  {
    if (!conn->isReading()) {
      INFO("write complete, start read");
      conn->startRead();
    }
  }

private:
  using ConnectionList = std::map<TcpConnectionPtr, Timestamp>;
  
  EventLoop*       loop_;
  TcpServer        server_;
  size_t           numThread_;
  Microsecond       timeout_;
  ConnectionList   connections_;
};

int main()
{
  EventLoop loop;
  setLogLevel(LOG_LEVEL_TRACE);
  InetAddress addr(9877);
  EchoServer server(&loop, addr, 4, 10s);
  server.start();
  // loop.runAfter(10s, [&](){
  //   int countdown = 5;
  //   INFO("server quit after %d second...", countdown);
  //   loop.runEvery(1s, [&, countdown]() mutable {
  //     INFO("server quit after %d second...", --countdown);
  //     if (countdown == 0)
  //         loop.quit();
  //   });
  // });

  loop.loop();
}