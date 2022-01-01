CFLAGS = -Wall -O2 -std=c99
LDLIBS = -lm -lncurses

all : cspeedtest

cspeedtest : cspeedtest.o curslib.o

clean :
	-rm -f cspeedtest
	-rm -f *.o
	-rm -f *~
