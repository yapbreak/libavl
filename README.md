# LibAvl

Libavl is a library to manage AVL structure to store and organize
everykind of data. You just need to implement function to compare,
to desallocate and to print your structure.

Please report bug at <adrien.oliva@yapbreak.fr>

Tracker on http://redmine.yapbreak.fr

## Installation

Since libAvl use autotools, you can run the following commands to
compile and install libavl:

	$ ./autogen.sh && ./configure && make && sudo make install

By default, installation prefix is /usr.

If you encounter any issue with libavl, you can add logs on stdoutput
with:

	$ ./configure --enable-log=#

where # is 0 for No log (default), 1 for Errors, 2 for Warnings,
3 for Information, 4 for Debug and 5 for Functions.

Moreover, you can add debug symbol with

	$ ./configure --enable-debug

## Test

Unit test can be performed by running

	$ make check

in root folder. If coverage is enabled, you can run

	$ make coverage

to get a full coverage report (you need lcov to get report).

## Licence

This work is published under the term of WTF-PL. You can find a copy
of licence term in COPYING file.
