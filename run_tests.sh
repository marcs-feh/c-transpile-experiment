#!/usr/bin/env sh

cc=gcc

set -xe
$cc -O0 -I. -L. -fPIE tests/run.c -o test.bin
./test.bin

