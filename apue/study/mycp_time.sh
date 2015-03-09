# !/bin/bash

for((i=0; i<20; i++));
do
  time ./mycp.out /home/zyx/bigfile temp $i;
done
