#include <src/Logger.h>
#include <src/EventLoop.h>

using namespace net;

int main()
{
  EventLoop loop;

  loop.runEvery(1s, [](){
      INFO("run every 1s");
  });
  loop.runAfter(10s, [&](){
      INFO("end after 10s");
      loop.quit();
  });
  loop.runAt(clock::nowAfter(15min), [&](){
      INFO("run 15min later");
  });

  INFO("start looping");
  loop.loop();
}