#!/bin/bash

echo 1 > tmp
gcc race.c -lpthread
./a.out
cat tmp
