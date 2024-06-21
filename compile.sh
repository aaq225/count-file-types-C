#!/bin/bash

module load gcc-7.1.0
make clean
make
if [ $? != 0 ]; then
  exit 1
fi
exit 0
