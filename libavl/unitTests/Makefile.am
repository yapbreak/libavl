ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

# Unit test for AVL
TESTS = avltest01\
		avltest02\
		avltest03\
		avltest04\
		avltest05\
		avltest06\
		avltest07\
		avltest08\
		avltest09\
		avltest10\
		avltest11\
		avltest12\
		avltest13

check_PROGRAMS = $(TESTS)

avltest01_SOURCES = avl_test01.c
avltest02_SOURCES = avl_test02.c
avltest03_SOURCES = avl_test03.c
avltest04_SOURCES = avl_test04.c
avltest05_SOURCES = avl_test05.c
avltest06_SOURCES = avl_test06.c
avltest07_SOURCES = avl_test07.c
avltest08_SOURCES = avl_test08.c
avltest09_SOURCES = avl_test09.c
avltest10_SOURCES = avl_test10.c
avltest11_SOURCES = avl_test11.c
avltest12_SOURCES = avl_test12.c
avltest13_SOURCES = avl_test13.c

AM_CFLAGS += -I..
LDADD = ../libavl.la

valgrind: $(TESTS)
	test -n "$(TESTS)" && sh $(top_srcdir)/valgrind-driver .

CLEANFILES = *.valgrind *.gcda *.gcno

