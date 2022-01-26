dnl Process with autoconf
AC_PREREQ(2.60)
AC_INIT([cspeedtest], [1.5.3], [birge@mit.edu])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_CHECK_HEADERS([ncurses.h sys/time.h math.h getopt.h])
AC_SEARCH_LIBS(floor, [m])
AC_SEARCH_LIBS(rand, [m])
AC_SEARCH_LIBS(sqrt, [m])
AC_SEARCH_LIBS(cos, [m])
AC_CHECK_FUNCS([atoi])
AC_CHECK_FUNCS([sqrt floor ceil round sin cos], [], [echo "math functions not found; exiting now."; exit-1])
AC_CHECK_FUNCS([gettimeofday], [], [echo "gettimeofday() needed, but not found; exiting now."; exit -1])
AC_CHECK_LIB([ncurses], [initscr], [], [echo "libncurses needed, but not found; exiting now."; exit -1])
AC_CHECK_FUNCS([getopt getopt_long])
AC_CHECK_FUNCS([nodelay])
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
