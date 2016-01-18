#!/bin/bash
cd src/stage2
make
cd ../..
./write_bootstage2.sh

