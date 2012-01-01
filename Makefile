CC = clang
CFLAGS = -Wall -O2 -std=c99 -lncurses
LIBS = -lcurses

all : cursbench

clean :
	-rm *~ cursbench
	-rm -df *.dSYM

