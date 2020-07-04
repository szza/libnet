#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

#include <src/InetAddress.h>
#include <src/EventLoop.h>
#include <src/Acceptor.h>
#include <src/Logger.h>

using namespace net;

namespace
{

int createSocket()
{
  int ret = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
  if (ret == -1)
      SYSFATAL("Acceptor::socket()");
  return ret;
}

} // unnamed-namespace

Acceptor::Acceptor(EventLoop* loop, const InetAddress& local)
: listening_(false),
  listenFd_(createSocket()),
  emfileFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC)),
  loop_(loop),
  listenChannle_(std::make_unique<Channel>(loop, listenFd_)),
  local_(local),
  newConnectionCallback_(nullptr)
{
  assert(emfileFd_ >0);
  assert(listenFd_ >0);
  assert(loop_);

  int on = 1;
  int ret = ::setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  if (ret == -1)
      SYSFATAL("Acceptor::setsockopt() SO_REUSEADDR");
  ret = ::setsockopt(listenFd_, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
  if (ret == -1)
      SYSFATAL("Acceptor::setsockopt() SO_REUSEPORT");
  ret = ::bind(listenFd_, local.getSockaddr(), local.getSocklen());
  if (ret == -1)
      SYSFATAL("Acceptor::bind()");
}

void Acceptor::listen()
{
  listening_ = true;
  loop_->assertInLoopThread();
  int ret = ::listen(listenFd_, SOMAXCONN-1);
  if (ret == -1)
      SYSFATAL("Acceptor::listen()");
  listenChannle_->setReadCallback([this]{this->handleRead();});
  listenChannle_->enableRead();
}


Acceptor::~Acceptor()
{
  assert(listening_);
  listening_ = false;
  listenChannle_->disableRead();
  listenChannle_->remove();
  if(listenFd_) ::close(listenFd_);
  if(emfileFd_) ::close(emfileFd_);
}

void Acceptor::handleRead()
{
  loop_->assertInLoopThread();

  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  int cfd=-1;
  while(1) { 
    cfd = ::accept4(listenFd_, 
                    reinterpret_cast<struct sockaddr*>(&addr),
                    &len, 
                    SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (cfd == -1) {
      switch(errno) { 
      case EWOULDBLOCK:
      case EINTR: 
        continue;
      case EMFILE:
        ::close(emfileFd_);
        emfileFd_ = ::accept(listenFd_, nullptr, nullptr);
        ::close(emfileFd_);
        emfileFd_= ::open("dev/null", O_CLOEXEC | O_RDONLY);
        continue;
      default:
        FATAL("unexpected accept4() error");
      }
    }
    else 
    {
      break;
    }
  }

  if (newConnectionCallback_) 
  {
    InetAddress peer;
    peer.setAddress(addr);
    newConnectionCallback_(cfd, local_, peer);
  }
  else 
  { 
    ::close(cfd);
  }
}
