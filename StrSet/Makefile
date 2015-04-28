CC=gcc
CXX=g++

SRC=strset.cc strsetconst.cc
OBJS=$(SRC:.cc=.o)

STANDARD=-Wall -std=c++11
DEBUG=-DDEBUG_ -g
RELASE=-O2


ifeq ($(debuglevel), 1)
	CXXFLAGS=$(STANDARD) $(DEBUG)
else
	CXXFLAGS=$(STANDARD) $(RELASE)
endif

all: $(OBJS)

strset.o: strset.cc strset.h

strsetconst.o: strsetconst.cc strsetconst.h

%.o: %.cc .FORCE
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY:	clean .FORCE

clean:
	rm -f $(OBJS) $(TESTOBJ) strset

.FORCE:

