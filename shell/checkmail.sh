#! /bin/sh

t=${1-60}

x="`ls -l $MAIL`"
while true
do
  y="`ls -l $MAIL`"
  echo $x $y
  x="$y"
  sleep $t
done | awk '$4<$12 {print "NEW MAIL"}'
