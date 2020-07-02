#include <unistd.h>
#include <sys/socket.h>
#include <assert.h>

#include <src/InetAddress.h>
#include <src/EventLoop.h>
#include <src/Logger.h>
#include <src/Connector.h>

using namespace net;

namespace
{

// fixme: duplicate code in Acceptor
int createSocket()
{
    int ret = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (ret == -1)
        SYSFATAL("Connector::socket()");
    return ret;
}

}

Connector::Connector(EventLoop* loop, const InetAddress& peer)
        : loop_(loop),
          peer_(peer),
          cfd_(createSocket()),
          connected_(false),
          started_(false),
          channel_(loop, cfd_)
{
    channel_.setWriteCallback([this](){ handleWrite();});
}

Connector::~Connector()
{
    if (!connected_)
        ::close(cfd_);
}

void Connector::start()
{
    loop_->assertInLoopThread();
    assert(!started_);
    started_ = true;

    int ret = ::connect(cfd_, peer_.getSockaddr(), peer_.getSocklen());
    if (ret == -1) {
        if (errno != EINPROGRESS)
            handleWrite();
        else
            channel_.enableWrite();
    }
    else handleWrite();
}

void Connector::handleWrite()
{
    loop_->assertInLoopThread();
    assert(started_);

    loop_->removeChannel(&channel_);

    int err;
    socklen_t len = sizeof(err);
    int ret = ::getsockopt(cfd_, SOL_SOCKET, SO_ERROR, &err, &len);
    if (ret == 0)
        errno = err;
    if (errno != 0) {
        SYSERR("Connector::connect()");
        if (errorCallback_)
            errorCallback_();
    }
    else if (newConnectionCallback_) {
        struct sockaddr_in addr;
        len = sizeof(addr);
        ret = ::getsockname(cfd_, reinterpret_cast<sockaddr*>(&addr), &len);
        if (ret == -1)
            SYSERR("Connection::getsockname()");
        InetAddress local;
        local.setAddress(addr);

        // now cfd_ is not belong to us
        connected_ = true;
        newConnectionCallback_(cfd_, local, peer_);
    }
}
