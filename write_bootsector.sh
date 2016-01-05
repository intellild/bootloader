#!/bin/bash
FILESIZ=`stat -c "%s" bin/bootstage2.bin`
sudo losetup /dev/loop0 disk.img
sudo dd if=bin/bootsector.bin of=/dev/loop0 bs=$FILESIZ count=1
sudo losetup -d /dev/loop0
