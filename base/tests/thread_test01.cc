// Author: Song Zhu

#include "Thread.h"
#include <stdio.h>

void func1() {
  printf("In func1, tid = %d, %s run in main thread\n",
      song::CurrentThread::tid(),
      song::CurrentThread::isMainThread() ? "" : "not");
}

void func2() {
  printf("In func2, tid = %d, %s run in main thread\n",
      song::CurrentThread::tid(),
      song::CurrentThread::isMainThread() ? "" : "not");
}

int main() {
  song::Thread t1(func1, "t1");
  song::Thread t2(func2, "t2");
  song::Thread t3(func2, "t2");
  t1.start();
  t2.start();
  t3.start();
  func1();
  func2();
  t1.join();
  t2.join();
  t3.join();
  return 0;
}