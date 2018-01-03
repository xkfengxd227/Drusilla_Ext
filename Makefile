SRCS=pri_queue.cpp util.cpp drusilla_select.cpp afn.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)

CXX?=g++ -std=c++11
CPPFLAGS=-w -O3

.PHONY: clean

all: $(OBJS)
	$(CXX) -o drusilla $(OBJS)

pri_queue.o: pri_queue.h

util.o: util.h

drusilla_select.o: drusilla_select.h

afn.o: afn.h

main.o:

clean:
	-rm $(OBJS) drusilla
