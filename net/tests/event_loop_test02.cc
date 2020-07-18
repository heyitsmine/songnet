#include "net/EventLoop.h"
#include "base/Thread.h"
#include <stdio.h>

song::EventLoop* g_loop;

void threadFunc()
{
  g_loop->loop();
}

int main()
{
  song::EventLoop loop;
  g_loop = &loop;
  song::Thread t(threadFunc);
  t.start();
  t.join();
}
