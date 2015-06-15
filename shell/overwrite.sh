#! /bin/sh

PATH=/bin:/usr/bin

case $# in
1) ;;
*) echo 'usage...' 1>&2; exit 2
esac

new=/tmp/overwr1.$$
old=/tmp/overwr2.$$
trap 'rm -f $new $old; exit 1' 1 2 15

cat >$new
cp $1 $old

trap '' 1 2 15
cp $new $1

rm -f $new $old

