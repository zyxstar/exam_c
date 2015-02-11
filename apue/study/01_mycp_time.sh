# !/bin/bash

for((i=0; i<5; i++));
do
  time ./01_mycp.out /home/zyx/cherrytree-0.30.5.tar temp $i;
done
