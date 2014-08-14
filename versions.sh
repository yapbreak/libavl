#!/bin/sh

PKGNAME="LibAvl"
REPORT="yapbreak@yapbreak.fr"

gittag=$(git describe --tags --always)

if echo $gittag | grep "[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*.*" > /dev/null 2>&1; then
    major=$(echo $gittag | sed 's|\([0-9][0-9]*\)\..*|\1|')
    minor=$(echo $gittag | sed 's|[0-9][0-9]*\.\([0-9][0-9]*\)\..*|\1|')
    build=$(echo $gittag | sed 's|[0-9][0-9]*\.[0-9][0-9]*\.\([0-9][0-9]*\).*|\1|')
else
    major=0
    minor=0
    build=0
fi

echo "Prepare $PKGNAME version ${major}.${minor}.${build}"

cp configure.pre configure.ac
sed -i "s|AC_INIT(.*)|AC_INIT([${PKGNAME}], [${gittag}], [${REPORT}])|" configure.ac
sed -i "s|___MAJOR___|$major|g" configure.ac
sed -i "s|___MINOR___|$minor|g" configure.ac
sed -i "s|___BUILD___|$build|g" configure.ac


