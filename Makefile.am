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

dist_check_SCRIPTS = test/testtest.sh test/helptest.sh test/linktest.sh
check_SCRIPTS = src/verstest.sh
check_DATA = src/cspeedtest-int
TESTS = $(dist_check_SCRIPTS) $(check_SCRIPTS)

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
