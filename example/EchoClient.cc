#include <iostream>
#include <thread>

#include <src/Logger.h>
#include <src/TcpConnection.h>
#include <src/TcpClient.h>
#include <src/EventLoop.h>

using namespace net;

class UserInput: noncopyable
{
public:
    UserInput(const TcpConnectionPtr& conn):
            conn_(conn)
    {
      conn_->setMessageCallback([this](auto connptr, auto buffer)
                                { 
                                  this->onMessage(connptr, buffer);
                                });
    }


    void onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
    {
      std::cout << buffer.retrieveAllAsString() << std::endl;
    }

    void run()
    {
        std::string line;
        while (std::getline(std::cin, line)) {
          conn_->send(line);
        }
        conn_->shutdown();
    }

private:
    TcpConnectionPtr conn_;
};

class EchoBench: noncopyable
{
public:
    EchoBench(EventLoop* loop, const InetAddress& addr):
            loop_(loop),
            client_(loop, addr)
    {
      client_.setConnectionCallback([this](auto connptr)
                                    { 
                                      this->onConnection(connptr);
                                    });
    }
    void start()
    { client_.start(); }

    void onConnection(const TcpConnectionPtr& conn)
    {
        INFO("connection %s is [%s]",
             conn->name().c_str(),
             conn->connected() ? "up" : "down");

        if (conn->connected()) {
            auto th = std::thread([conn](){
                UserInput user(conn);
                user.run();
            });
            th.detach();
        }
        else {
            loop_->quit();
        }
    }


private:
    EventLoop* loop_;
    TcpClient client_;
};

int main()
{
    setLogLevel(LOG_LEVEL_WARN);
    EventLoop loop;
    InetAddress addr("127.0.0.1", 9877);
    EchoBench client(&loop, addr);
    client.start();
    loop.loop();
}