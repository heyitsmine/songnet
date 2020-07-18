LIB_SRC = ../EventLoop.cc
BINARIES = event_loop_test01 event_loop_test02

CXXFLAGS = -O0 -g  -Wall -I ../.. -pthread
LDFLAGS = -lpthread
BASE_SRC = ../../base/Thread.cc

all: $(BINARIES)

$(BINARIES):
	g++ $(CXXFLAGS) -o $@ $(LIB_SRC) $(BASE_SRC) $(filter %.cc,$^) $(LDFLAGS)

event_loop_test01: event_loop_test01.cc
event_loop_test02: event_loop_test02.cc

.PHONY : clean
clean:
	rm -f $(BINARIES) core
