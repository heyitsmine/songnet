LIB_SRC = ../Thread.cc
BINARIES = thread_test01

CXXFLAGS = -O0 -g  -Wall -I .. -pthread
LDFLAGS = -lpthread
BASE_SRC = 

all: $(BINARIES)

$(BINARIES):
	g++ $(CXXFLAGS) -o $@ $(LIB_SRC) $(BASE_SRC) $(filter %.cc,$^) $(LDFLAGS)

thread_test01: thread_test01.cc

.PHONY : clean
clean:
	rm -f $(BINARIES) core
