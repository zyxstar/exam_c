#! /bin/sh

PATH=/bin:/usr/bin
new=/tmp/wwho1.$$
old=/tmp/wwho2.$$
>$old

trap 'rm -f $new $old; exit 1' 1 2 15

while true
do
  who>$new
  diff $old $new
  mv $new $old
  sleep 1
done | awk '/>/ {$1 = "in:   "; print}
            /</ {$1 = "out:  "; print}'

