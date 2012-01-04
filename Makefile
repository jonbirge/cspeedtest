CFLAGS = -Wall -O2 -std=c99 -lncurses

all : cursbench

clean :
	-rm *~ cursbench
	-rm -df *.dSYM

