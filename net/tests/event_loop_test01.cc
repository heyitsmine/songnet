// Author: Song Zhu
// 
// 在主线程和子线程分别创建一个EventLoop

#include "net/EventLoop.h"
#include "base/Thread.h"
#include <stdio.h>
#include <unistd.h>

void threadFunc()
{
  printf("threadFunc(): pid = %d, tid = %d\n",
         getpid(), song::CurrentThread::tid());

  song::EventLoop loop;
  loop.loop();
}

int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), song::CurrentThread::tid());

  song::EventLoop loop;

  song::Thread thread(threadFunc);
  thread.start();

  loop.loop();
  pthread_exit(NULL);
}