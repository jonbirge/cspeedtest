UCFLAGS = -Wall -O2 -std=c99
LDLIBS = -lm -lncurses

all : cursbench

cursbench : cursbench.o curslib.o

clean :
	-rm cursbench
	-rm *.o
	-rm *~
  