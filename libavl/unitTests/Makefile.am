ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

# Unit test for AVL
TESTS = avltest
check_PROGRAMS = avltest

avltest_SOURCES = avl_tests.c\
                  avl_test01.c\
                  avl_test02.c\
                  avl_test03.c\
                  avl_test04.c\
                  avl_test05.c\
                  avl_test06.c\
                  avl_test07.c\
                  avl_test08.c\
                  avl_test09.c\
                  avl_test10.c\
                  avl_test11.c
avltest_CFLAGS = -I..
avltest_LDADD = ../libavl.la

