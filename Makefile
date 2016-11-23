UNIXOS = $(shell uname -s)

all : cursbench

ifeq ($(UNIXOS),Linux)
  include Makefile.linux
endif

ifeq ($(UNIXOS),Darwin)
  include Makefile.osx
endif
