CFLAGS = -Wall -O2 -std=c99
LDLIBS = -lm -lncurses

all : cursbench

cursbench : cursbench.o curslib.o

clean :
	-rm -f cursbench
	-rm -f *.o
	-rm -f *~
