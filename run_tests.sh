#!/usr/bin/env sh

cc=gcc

samu -v -j6
set -xe
rm bin/main.o
$cc -O0 -I. -L. -fPIE tests/run.c -o test.bin bin/*
./test.bin

