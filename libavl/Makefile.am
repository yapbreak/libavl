ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libavl.la
include_HEADERS = avl.h

libavl_la_SOURCES = avl.c
libavl_la_CFLAGS = $(AM_CFLAGS) -fPIC
libavl_la_LDFLAGS = -version-info @VERSION_CURRENT@:@VERSION_REVISION@:@VERSION_AGE@

SUBDIRS = unitTests

avlextradir = $(prefix)/lib/pkgconfig
avlextra_DATA = avl.pc
