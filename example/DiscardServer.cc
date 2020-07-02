#include <src/Logger.h>
#include <src/EventLoop.h>
#include <src/TcpConnection.h>
#include <src/TcpServer.h>

using namespace net;

class DiscardServer
{
public:
  DiscardServer(EventLoop* loop, const InetAddress& addr)
  : server(loop, addr)
  {
    server.setMessageCallback([this](auto connptr, auto buffer) 
                              { 
                                this->onMessage(connptr, buffer);
                              });
  }

  void start()
  { server.start(); }

  void onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
  {
    TRACE("connection %s recv %lu bytes",
          conn->name().c_str(),
          buffer.readableBytes());
    buffer.retrieveAll();
  }

private:
  TcpServer server;
};

int main()
{
  //setLogLevel(LOG_LEVEL_TRACE);
  EventLoop loop;
  InetAddress addr(9877);
  DiscardServer server(&loop, addr);
  server.start();
  loop.loop();
}
