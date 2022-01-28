dnl Build tools
AC_PREREQ(2.60)
AC_INIT([cspeedtest], [1.5.5], [birge@mit.edu])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

dnl Library dependency checking
AC_CHECK_HEADERS([ncurses.h sys/time.h math.h getopt.h])
AC_SEARCH_LIBS([floor], [m])
AC_SEARCH_LIBS([rand], [m])
AC_SEARCH_LIBS([sqrt], [m])
AC_SEARCH_LIBS([cos], [m])
AC_CHECK_FUNCS([sqrt floor ceil round sin cos], [], AC_MSG_ERROR([math functions not found!]))
AC_CHECK_FUNCS([gettimeofday], [], AC_MSG_ERROR([gettimeofday() not found!]))
AC_CHECK_LIB([ncurses], [initscr], [], AC_MSG_ERROR([libncurses not found!]))
AC_CHECK_FUNCS([getopt getopt_long])
AC_CHECK_FUNCS([nodelay])
AC_CHECK_FUNCS([atoi])

dnl Generate files
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT

