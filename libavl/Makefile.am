ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libavl.la
include_HEADERS = avl.h

libavl_la_SOURCES = avl.c
libavl_la_CFLAGS = $(AM_CFLAGS) -fPIC
libavl_la_LDFLAGS = -version-info @VERSION_MAJOR@:@VERSION_MINOR@:@VERSION_BUILD@

SUBDIRS = unitTests
