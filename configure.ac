dnl Autotools
AC_PREREQ([2.60])
AC_INIT([cspeedtest], [1.9.3-alpha], [bugs@birge.us])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_SRCDIR([src/cspeedtest.c])
AC_CONFIG_HEADERS([config.h])

dnl Build tool checks
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

dnl Critical dependency checking
AC_FUNC_MALLOC
AC_CHECK_HEADERS([ncurses.h stdlib.h sys/time.h getopt.h math.h], [], [AC_MSG_ERROR([HEADERS NOT FOUND! UNABLE TO CONTINUE.])])
AC_CHECK_LIB([ncurses], [initscr], [], AC_MSG_ERROR([LIBNCURSES NOT FOUND! PLEASE INSTALL BEFORE PROCEEDING.]))
AC_SEARCH_LIBS([rand], [m], [], [ AC_MSG_ERROR([rand() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([cos], [m], [], [ AC_MSG_ERROR([cos() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([sin], [m], [], [ AC_MSG_ERROR([sin() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([sqrt], [m], [], [ AC_MSG_ERROR([sqrt() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([ceil], [m], [], [ AC_MSG_ERROR([ceil() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([floor], [m], [], [ AC_MSG_ERROR([floor() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_SEARCH_LIBS([round], [m], [], [ AC_MSG_ERROR([round() NOT FOUND! UNABLE TO CONTINUE.]) ])
AC_CHECK_FUNCS([gettimeofday], [], [], [ AC_MSG_ERROR([gettimeofday() NOT FOUND! UNABLE TO CONTINUE.]) ])

dnl Non-fatal function checks
AC_CHECK_FUNCS([getopt getopt_long])
AC_CHECK_FUNCS([atoi])

dnl Generate files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
