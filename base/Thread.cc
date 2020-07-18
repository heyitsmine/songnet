// Author: Song Zhu

#include "Thread.h"

#include <memory>
#include <cassert>

#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace song {

namespace CurrentThread {

  __thread const char* t_threadName = "unknown";

} //  namespace song::CurrentThread

} // namespace song

namespace {

__thread pid_t t_cachedTid = 0;

// 获取线程id
pid_t gettid() {
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

struct ThreadData {
  typedef song::Thread::ThreadFunc ThreadFunc;
  ThreadFunc func_;
  std::string name_;
  std::weak_ptr<pid_t> wkTid_;

  ThreadData(
      const ThreadFunc& func,
      const std::string& name,
      const std::shared_ptr<pid_t>& tid)
      : func_(func),
        name_(name),
        wkTid_(tid) {}

  void runInThread() {
    pid_t tid = song::CurrentThread::tid();
    std::shared_ptr<pid_t> ptid = wkTid_.lock();

    if (ptid) {
      *ptid = tid;
      ptid.reset();
    }

    song::CurrentThread::t_threadName = name_.empty() ? "songThread" : name_.c_str();
    ::prctl(PR_SET_NAME, song::CurrentThread::t_threadName);
    func_(); // FIXME: surround with try-catch, see muduo
    song::CurrentThread::t_threadName = "finished";
  }
};

void* startThread(void* obj) {
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->runInThread();
  delete data;
  return NULL;
}

} // namespace ::

using namespace song;

pid_t CurrentThread::tid() {
  if (t_cachedTid == 0) {
    t_cachedTid = gettid();
  }
  return t_cachedTid;
}

const char* CurrentThread::name() {
  return t_threadName;
}

bool CurrentThread::isMainThread() {
  return tid() == ::getpid();
}


Thread::Thread(
    const ThreadFunc &func,
    const std::string &name)
    : started_(false),
      joined_(false),
      pthreadId_(0),
      tid_(new pid_t(0)),
      func_(std::move(func)), // XXX: std::move(func)之后，func还可调用吗？
      name_(name) {}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_detach(pthreadId_);
  }
}

void Thread::start() {
  assert(!started_);
  started_ = true;
  
  ThreadData *data = new ThreadData(func_, name_, tid_);
  if (pthread_create(&pthreadId_, NULL, &startThread, data));
}

void Thread::join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  pthread_join(pthreadId_, NULL);
}