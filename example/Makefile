# Example of Makefile to build program using libavl shared library

.PHONY: all clean distclean

all: example.x

example.o: example.c
	gcc -g -o example.o -c example.c

example.x: example.o
	gcc -o example.x example.o -lavl

clean:
	rm -rf example.o

distclean: clean
	rm -rf example.x

