dnl Process with autoconf
AC_INIT([cspeedtest], [1.4.2], [birge@mit.edu])
AC_PREREQ(2.5)
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_INSTALL
AC_PROG_LN_S
AC_SEARCH_LIBS(ceil, [m])
AC_SEARCH_LIBS(rand, [m])
AC_SEARCH_LIBS(sqrt, [m])
AC_SEARCH_LIBS(sin, [m])
AC_SEARCH_LIBS(cos, [m])
AC_CHECK_LIB(ncurses, initscr, [], [echo "libncurses needed, but not found; exiting now."; exit -1])
AC_HEADER_STDC
AC_CHECK_HEADERS([ncurses.h sys/time.h math.h])
AC_CHECK_FUNCS(getopt)
AC_CHECK_FUNCS(nodelay)
AC_CHECK_FUNCS(gettimeofday, [], [echo "gettimeofday() needed, but not found; exiting now."; exit -1])
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
