UNIXOS = $(shell uname -s)

all : cursbench

cursbench : cursbench.o curslib.o

ifeq ($(UNIXOS),Linux)
  include Makefile.linux
endif

ifeq ($(UNIXOS),Darwin)
  include Makefile.osx
endif

clean :
	-rm cursbench
	-rm *.o
	-rm *~
  