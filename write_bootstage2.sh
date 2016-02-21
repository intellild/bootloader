#!/bin/bash
FILESIZ=`stat -c "%s" bin/bootstage2.bin`
sudo losetup /dev/loop0 -o 1024 disk.img
sudo dd if=bin/bootstage2.bin of=/dev/loop0 bs=$FILESIZ count=1
sudo losetup -d /dev/loop0
