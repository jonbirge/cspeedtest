
bin_PROGRAMS = src/cspeedtest

src_cspeedtest_SOURCES = src/curslib.c src/curslib.h src/timecurses.c src/timecurses.h src/cspeedtest.c \
  src/random_screen.c src/swirl_screen.c src/sphere_screen.c

src_cspeedtest_CFLAGS = -std=c99 -Wall

install-exec-local:
	ln $(DESTDIR)$(bindir)/cspeedtest $(DESTDIR)$(bindir)/cspeedtest-int

check_SCRIPTS = test/verstest.sh
check_DATA = test/cspeedtest-int
TESTS = $(check_SCRIPTS) test/testtest.sh test/helptest.sh test/linktest.sh

test/verstest.sh:
	echo '$(bin_PROGRAMS) --version | grep "@PACKAGE_STRING@"' > $@
	chmod +x $@

# Overrides default
test/cspeedtest-int: $(bin_PROGRAMS)
	rm -f $@
	ln src/cspeedtest $@

CLEANFILES = $(check_SCRIPTS) $(check_DATA)
