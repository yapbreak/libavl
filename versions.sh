#!/bin/sh

PKGNAME="LibAvl"
REPORT="yapbreak@yapbreak.fr"

gittag=$(git describe --tags --always)
sed "s|AC_INIT(.*)|AC_INIT([${PKGNAME}], [${gittag}], [${REPORT}])|" configure.pre > configure.ac
