dnl Autotools
AC_PREREQ([2.60])
AC_INIT([cspeedtest], [1.8.6], [bugs@birge.us])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_SRCDIR([src/cspeedtest.c])
AC_CONFIG_HEADERS([config.h])

dnl Build tool checks
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

dnl Dependency checking
AC_FUNC_MALLOC
AC_CHECK_HEADERS([ncurses.h stdlib.h sys/time.h getopt.h math.h])
AC_CHECK_LIB([ncurses], [initscr], [], AC_MSG_ERROR([libncurses not found!]))
AC_SEARCH_LIBS([round], [m])
AC_SEARCH_LIBS([rand], [m])
AC_SEARCH_LIBS([sqrt], [m])
AC_CHECK_FUNCS([ceil floor cos], [], AC_MSG_ERROR([math functions not found!]))
AC_CHECK_FUNCS([gettimeofday], [], AC_MSG_ERROR([gettimeofday() not found!]))
AC_CHECK_FUNCS([getopt getopt_long])
AC_CHECK_FUNCS([atoi])

dnl Generate files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
