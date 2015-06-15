#! /bin/sh

case $# in
0) echo 'Usage...'
esac

for i in `echo $PATH | sed 's/:/ /g'`
do
	if test -f $i/$1
	then
		echo $i/$1
		exit 0
  fi
done
exit 1
