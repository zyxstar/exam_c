#!/bin/bash

echo 1 > tmp
gcc race.c -Wall
./a.out
cat tmp
