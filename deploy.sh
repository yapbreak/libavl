#!/bin/sh

if [ "x$1" == "x" ]; then
    tag="$(git tag | tail -n 1)"
else
    tag="$1"
fi

package=$(pwd | sed 's|.*/||')
base="${package}_${tag}"

archive="${base}.tar.gz"
checksum="${base}.md5"
signature="${base}.sig"

echo "Build archive ${archive}"
/usr/bin/git archive --format=tar.gz "${tag}" > "${archive}"
echo "Compute checksum"
/usr/bin/md5sum "$archive" > "${checksum}"
echo "Sign tarball"
/usr/bin/gpg --detach-sign\
             --armor\
             --local-user "adrien.oliva@yapbreak.fr"\
             --output "${signature}"\
             "${archive}"
echo "Verify checksum"
/usr/bin/md5sum --check "${checksum}"
echo "Verify signature"
/usr/bin/gpg --verify "${signature}" "${archive}"



