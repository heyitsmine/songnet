// Author: Song Zhu

#ifndef SONG_NET_EVENTLOOP_H
#define SONG_NET_EVENTLOOP_H

#include "base/Thread.h"

namespace song {

class EventLoop : noncopyable {
public:
	EventLoop();
	~EventLoop();

	void loop();

	void assertInLoopThread() {
		if (!isInLoopThread()) {
			abortNotInLoopThread();
		}
	}

	bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

private:

	void abortNotInLoopThread();

	bool looping_;
	const pid_t threadId_;
};

}

#endif // !SONG_NET_EVENTLOOP_H