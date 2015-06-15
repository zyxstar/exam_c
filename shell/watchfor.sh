#! /bin/sh

case $# in
0) echo 'Usage...'
esac

until who | egrep "$1"
do
  sleep 1
done
