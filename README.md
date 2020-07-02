# libnet: A multithreaded C++ network library

## 简介

`libnet` 是仿照muduo[1]实现的一个基于Reactor模式的多线程C++网络库，经过适当简化以后代码量约为2000行。简化的部分如下：
- 使用c++11的std::atomic 库 来替代GCC 内置的原子指令。

  比如在 `TcpConnection`中`shutdown`函数对于连接状态`state_`的修改：
  ```cpp
    void TcpConnection::shutdown()
    {
      assert(state_ <= kDisconnecting);
      if (state_.exchange(kDisconnecting) ==kConnected) {
        if (loop_->isInLoopThread())
        {
          shutdownInLoop();
        }
        else 
        {
          loop_->queueInLoop([this]
                            { 
                              this->shutdownInLoop();
                            });
        }
      }
    }
  ```
- 多线程依赖于C++11提供的std::thread库，而不是重新封装POSIX thread API。

- 定时器依赖于C++11提供的std::chrono库，而不是自己实现Timstamp类，也不用直接调用`gettimeofday()`。这样写的好处之一是我们不必再为定时器API的时间单位操心：

  ```c++
  using namespace std::literals::chrono_literals;
  loop.runEvery(10s, [](){INFO("run every 10 seconds");});
  loop.runAfter(24h, [](){INFO("run after 24 hours");});
  loop.runAt(Clock::nowAfter(15min), [](){INFO("run 15 minutes later");});
  ```

- 默认为accept socket开启SO_RESUEPORT选项，这样每个线程都有自己的Acceptor，就不必在线程间传递connection socket。开启该选项后内核会将TCP连接分摊给各个线程，因此不必担心负载均衡的问题。

- 仅具有简单的日志输出功能，用于调试。

- 仅使用epoll，不使用poll和select。

- 使用c++14的`Lambada`表达式 与`auto`组合，完美替代`std::bind`与`std::placeholders`的组合，更加方便地将成员函数作为回调函数，不仅更加简洁，也可以获得更高的效率。

  一个简单的echo服务器。以前的实现：

  ```C++
  class EchoServer: noncopyable
  {
  public:
    EchoServer(EventLoop* loop, const InetAddress& addr)
      : loop_(loop),
        server_(loop, addr),
    {
      // set echo callback
      // 使用的是 std::bind
      server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1, _2));
    }
    void start() { server_.start(); }
    void onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
    {
      // echo message
      conn->send(buffer);
    }
  private:
    EventLoop* loop_;
    TcpServer server_;
  };
  ```
  现在的实现：
  ```cpp
  class EchoServer: noncopyable
  {
  public:
    EchoServer(EventLoop* loop, const InetAddress& addr)
      : loop_(loop),
        server_(loop, addr),
    {
      // 可以使用 lambda + auto 来替代 上面的 std::bind + _1 ,_2的组合
      // 实现更加简洁
      server_.setMessageCallback([this](auto connptr, auto buffer)
                                 { 
                                  this->onMessage(connptr, buffer);
                                 });
    }
    void start() { server_.start(); }
    void onMessage(const TcpConnectionPtr& conn, Buffer& buffer)
    {
      // echo message
      conn->send(buffer);
    }
  private:
    EventLoop* loop_;
    TcpServer server_;
  };
  ```
- 应用层的流量控制

  上面的这个 `echo` 实现非常简单，读者只需关注 `onMessage` 回调函数，它将收到消息发回客户端。然而，该实现有一个问题：若客户端只发送而不接收数据（即只调用`write`而不调用`read`），则TCP的流量控制（flow control）会导致数据堆积在服务端，最终会耗尽服务端内存。为解决该问题我们引入应用层的流量控制高/低水位回调：

  ```c++
  class EchoServer: noncopyable
  {
  public:
    ...
    void onConnection(const TcpConnectionPtr& conn)
    {
      if (conn->connected())
          conn->setHighWaterMarkCallback([this](auto connptr, auto mark)
                                          {
                                            this->onHighWaterMark(connptr, mark);
                                          },
                                          1024);
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
    ...
  };
  ```

  我们新增了3个回调：`onConnection`，`onHighWaterMark`和`onWriteComplete`。当TCP连接建立时`onConnection`会设置高水位回调值（high water mark）；当send buffer达到该值时，`onHighWaterMark`会停止读socket；当send buffer全部写入内核时，`onWriteComplete`会重新开始读socket。

  除此以外，我们还需要给服务器加上定时功能以清除空闲连接。实现思路是让服务器保存一个TCP连接的`std::map`，每隔几秒扫描一遍所有连接并清除超时的连接，代码在[这里](./example/EchoServer.cc)。

  然后，我们给服务器加上多线程功能。实现起来非常简单，只需加一行代码即可：

  ```c++
  EchoServer::void start()
  {
    // set thread num here
    server_.setNumThread(2);
    server_.start();
  }
  ```

  最后，完整的代码可以参考 `example/EchoServer.cc`

- 使用`using`来代替`typedef`，使得代码更加符合现代c++风格。

- 对于 `epoll_wait`的阻塞时间，不是一个固定值，而是根据是否有其他任务和定时器最早的超时时间来计算的，来减少阻塞时间，加快响应。
  ```cpp
    // EventLoop.h
    int  getNextTimeout() { 
      if(!pendingTasks_.empty()) { 
        return 0;
      } 
      // 获取最早的超时时间
      return static_cast<int>(timerQueue_->nextTimeout());
    }

    // EventLoop.cc
    int timeout = getNextTimeout();
    poller_->poll(activeChannels_, timeout);
  ```
- `TimeWheel`：可以为每个连接对象设置超时时间，在O(1)时间复杂度内可以剔除超时连接。

整个程序在正常使用下，使用 `valgrind`工具检测内存，无内存泄露。以`echo_server`为例：
  ```bash
    ==6199== 
    ==6199== HEAP SUMMARY:
    ==6199==     in use at exit: 0 bytes in 0 blocks
    ==6199==   total heap usage: 68 allocs, 68 frees, 107,402 bytes allocated
    ==6199== 
    ==6199== All heap blocks were freed -- no leaks are possible
    ==6199== 
    ==6199== For lists of detected and suppressed errors, rerun with: -s
    ==6199== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
  ```
## 编译运行

```bash
  mkdir build && cd build
  cmake ..
  make -j 12 # 根据自己电脑线程设置
```

## 笔记

网络库的具体实现方法参考 [我的github关于网络编程博客](https://github.com/szza/LearningNote/tree/master/8.%E5%BC%80%E6%BA%90%E9%A1%B9%E7%9B%AE)。

## 参考

[[1]](https://github.com/chenshuo/muduo) Muduo is a multithreaded C++ network library based on the reactor pattern.