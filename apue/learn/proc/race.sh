#!/bin/bash

echo 1 > tmp
gcc race_lock.c
./a.out
cat tmp
