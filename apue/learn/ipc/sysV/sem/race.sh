#!/bin/bash

echo 1 > tmp
gcc race.c
./a.out
cat tmp
