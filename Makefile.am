bin_PROGRAMS = src/cspeedtest

src_cspeedtest_SOURCES = src/curslib.c src/curslib.h src/timecurses.c src/timecurses.h src/cspeedtest.c \
  src/random_screen.c src/swirl_screen.c src/disk_screen.c src/sphere_screen.c

src_cspeedtest_CFLAGS = -std=c99 -Wall

check_SCRIPTS = src/verstest.sh src/helptest.sh
TESTS = $(check_SCRIPTS)

src/verstest.sh:
	echo './src/cspeedtest --version | grep "cspeedtest"' > src/verstest.sh
	chmod +x src/verstest.sh

src/helptest.sh:
	echo './src/cspeedtest --help | grep "Usage"' > src/helptest.sh
	chmod +x src/helptest.sh

CLEANFILES = $(check_SCRIPTS)
