#!/bin/sh

PKGNAME="LibAvl"
REPORT="yapbreak@yapbreak.fr"

gittag=$(git describe --tags --always)

if echo $gittag | grep "[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*.*" > /dev/null 2>&1; then
    current=$(echo $gittag | sed 's|\([0-9][0-9]*\)\..*|\1|')
    age=$(echo $gittag | sed 's|[0-9][0-9]*\.\([0-9][0-9]*\)\..*|\1|')
    revision=$(echo $gittag | sed 's|[0-9][0-9]*\.[0-9][0-9]*\.\([0-9][0-9]*\).*|\1|')
else
    current=0
    age=0
    revision=0
fi

echo "Prepare $PKGNAME version $(( ${current} - ${age} )).${age}.${revision}"

cp configure.pre configure.ac
sed -i "s|AC_INIT(.*)|AC_INIT([${PKGNAME}], [${gittag}], [${REPORT}])|" configure.ac
sed -i "s|___CURRENT___|$current|g" configure.ac
sed -i "s|___REVISION___|$revision|g" configure.ac
sed -i "s|___AGE___|$age|g" configure.ac


