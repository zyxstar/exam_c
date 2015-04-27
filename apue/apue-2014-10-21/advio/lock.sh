#!/bin/bash

echo 1 > tmp
gcc lock.c
./a.out
cat tmp
