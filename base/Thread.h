// Author: Song Zhu

#ifndef SONG_BASE_THREAD_H
#define SONG_BASE_THREAD_H

#include <functional>
#include <pthread.h>
#include <string>
#include <memory>

#include "noncopyable.h"

namespace song {

class Thread : noncopyable {
 public:
  typedef std::function<void ()> ThreadFunc;
  explicit Thread(const ThreadFunc&, const std::string &name = std::string());
  ~Thread();

  void start();
  void join();

  bool started() { return started_; }
  const std::string& name() const {return name_; }
 
 private:
  bool started_;
  bool joined_;
  pthread_t pthreadId_;
  std::shared_ptr<pid_t> tid_;
  ThreadFunc func_;
  std::string name_;

  // TODO: 添加numCreated_,记录创建线程数量
};

namespace CurrentThread {
  pid_t tid();
  const char* name();
  bool isMainThread();
}

}

#endif // !SONG_BASE_THREAD_H
