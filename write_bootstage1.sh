#!/bin/sh
FILESIZ=`stat -c "%s" bin/bootstage2.bin`
sudo losetup /dev/loop0 -o 512 disk.img
sudo dd if=bin/bootstage1.bin of=/dev/loop0 bs=$FILESIZ count=1
sudo losetup -d /dev/loop0
