#! /bin/sh

PATH=/bin:/usr/bin

IFS='
'

case $# in
0) echo 'usage...' 1>&2; exit 1
esac

kill `./pick.sh \`ps -aux | grep "$*"\` | awk '{print $2}'`
