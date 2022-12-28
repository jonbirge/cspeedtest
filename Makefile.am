
bin_PROGRAMS = src/cspeedtest

src_cspeedtest_SOURCES = src/curslib.c src/curslib.h src/timecurses.c src/timecurses.h src/cspeedtest.c \
  src/random_screen.c src/swirl_screen.c src/sphere_screen.c

src_cspeedtest_CFLAGS = -std=c99 -Wall

install-exec-local:
	ln $(DESTDIR)$(bindir)/cspeedtest $(DESTDIR)$(bindir)/cspeedtest-int

uninstall-local:
	rm -f $(DESTDIR)$(bindir)/cspeedtest-int

dist_check_SCRIPTS = test/testtest.sh test/helptest.sh test/linktest.sh
check_SCRIPTS = src/verstest.sh
check_DATA = src/cspeedtest-int
TESTS = $(dist_check_SCRIPTS) $(check_SCRIPTS)

src/verstest.sh:
	rm -f $@
	echo '$(bin_PROGRAMS) --version | grep "@PACKAGE_STRING@"' > $@
	chmod +x $@

src/cspeedtest-int: $(bin_PROGRAMS)
	rm -f $@
	ln src/cspeedtest $@

CLEANFILES = $(check_SCRIPTS) $(check_DATA)
