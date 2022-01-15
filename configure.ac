AC_INIT([cspeedtest], [1.2], [birge@mit.edu])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_PROG_INSTALL
AC_SEARCH_LIBS(ceil, [m])
AC_SEARCH_LIBS(rand, [m])
AC_CHECK_LIB(ncurses, initscr)
AC_CHECK_HEADERS([ncurses.h sys/time.h math.h])
AC_CHECK_FUNCS([getopt])
AC_CHECK_FUNCS([gettimeofday], [], [echo "gettimeofday() not found."; exit -1])
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
