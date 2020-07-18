// Author: Song Zhu

#include "EventLoop.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <poll.h>
using namespace song;

__thread EventLoop* t_loopInThisThread = nullptr;

EventLoop::EventLoop()
  : looping_(false),
    threadId_(CurrentThread::tid()) {
      if (t_loopInThisThread) {
        // FIXME: 使用日志
        std::cerr << "Another EventLoop " << t_loopInThisThread
              << " exists in this thread " << threadId_;
        std::abort();
      } else {
        t_loopInThisThread = this;
      }
    }

EventLoop::~EventLoop() {
  assert(!looping_);
  t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;

  ::poll(NULL, 0, 5*1000);

  looping_ = false;
}

void EventLoop::abortNotInLoopThread() {
  // FIXME: 使用日志
  std::cerr << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " <<  CurrentThread::tid();
  std::abort();
}