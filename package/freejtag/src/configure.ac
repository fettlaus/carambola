dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([FreeJTAG], [0.0.1])


AC_CANONICAL_SYSTEM
AC_CONFIG_SRCDIR([src/freejtag.c])
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_CONFIG_HEADERS([src/config.h])
PKG_CHECK_MODULES(CHECK,[check >= 0.9.8])
PKG_CHECK_MODULES(GLIB,[glib-2.0 >= 2.26.1] gio-2.0)

CFLAGS="$CFLAGS $GLIB_CFLAGS -pedantic -std=c99"
LIBS="$LIBS $GLIB_LIBS"
AM_CPPFLAGS=-DSYSCONFDIR='${sysconfdir}'
AC_SUBST([AM_CPPFLAGS])

AC_CONFIG_FILES([
Makefile
src/Makefile
tests/Makefile
])

AC_OUTPUT

