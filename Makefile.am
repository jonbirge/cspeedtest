# Compilation

bin_PROGRAMS = src/cspeedtest

src_cspeedtest_SOURCES = src/curslib.c src/curslib.h src/timecurses.c src/timecurses.h \
src/cspeedtest.c src/random_screen.c src/swirl_screen.c src/sphere_screen.c

src_cspeedtest_CFLAGS = -std=c99 -Wall


# Installation

install-exec-local:
	ln -f $(DESTDIR)$(bindir)/cspeedtest $(DESTDIR)$(bindir)/cspeedtest-int

uninstall-local:
	rm -f $(DESTDIR)$(bindir)/cspeedtest-int

src/cspeedtest-int$(EXEEXT): $(bin_PROGRAMS)
	rm -f $@
	ln src/cspeedtest $@


# Testing

dist_check_SCRIPTS = test/testtest.sh test/helptest.sh test/linktest.sh \
	test/timeflagtest.sh test/invalidtimetest.sh test/extendedtest.sh \
	test/interactivehelptest.sh test/inthelptest.sh test/bugreporttest.sh
check_SCRIPTS = src/verstest.sh
check_PROGRAMS = test/curslib_unit test/timecurses_unit
check_DATA = src/cspeedtest-int
TESTS = $(dist_check_SCRIPTS) $(check_SCRIPTS) $(check_PROGRAMS)

test_curslib_unit_SOURCES = test/curslib_unit.c src/curslib.c
test_timecurses_unit_SOURCES = test/timecurses_unit.c src/timecurses.c \
	src/random_screen.c src/sphere_screen.c src/swirl_screen.c src/curslib.c

src/verstest.sh:
	rm -f $@
	echo '$(bin_PROGRAMS) --version | grep "@PACKAGE_STRING@"' > $@
	chmod +x $@


# Documentation

dist_man_MANS = man/cspeedtest.1 man/cspeedtest-int.1

man/cspeedtest.1:
	pandoc -s -t man man/cspeedtest.1.md -o $@

man/cspeedtest-int.1:
	pandoc -s -t man man/cspeedtest-int.1.md -o $@


# Cleaning

CLEANFILES = $(check_SCRIPTS) $(check_DATA)
