AC_INIT([cspeedtest], [1.2], [birge@mit.edu])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_PROG_INSTALL
AC_SEARCH_LIBS(ceil, [m])
AC_SEARCH_LIBS(rand, [m])
AC_CHECK_LIB(ncurses, initscr)
AC_CHECK_FUNCS([initscr clrtoeol init_pair nodelay getmaxyx])
AC_CHECK_FUNC(getopt)
AC_CHECK_FUNC(gettimeofday)
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
