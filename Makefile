CC = gcc
CFLAGS = -Wall -O2 -std=c99 -lncurses
LIBS = -lcurses

all : curstest

clean :
	-rm *~ curstest
	-rm -df *.dSYM

