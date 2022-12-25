
bin_PROGRAMS = src/cspeedtest

src_cspeedtest_SOURCES = src/curslib.c src/curslib.h src/timecurses.c src/timecurses.h src/cspeedtest.c \
  src/random_screen.c src/swirl_screen.c src/sphere_screen.c

src_cspeedtest_CFLAGS = -std=c99 -Wall

check_SCRIPTS = test/verstest.sh
check_PROGRAMS = test/cspeedtest-int
TESTS = $(check_SCRIPTS) test/testtest.sh test/helptest.sh test/linktest.sh

test/verstest.sh:
	echo '$(bin_PROGRAMS) --version | grep "@PACKAGE_STRING@"' > $@
	chmod +x $@

test/cspeedtest-int$(EXEEXT): $(bin_PROGRAMS)
	ln src/cspeedtest test/cspeedtest-int

CLEANFILES = $(check_SCRIPTS)
