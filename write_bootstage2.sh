#!/bin/sh
sudo losetup /dev/loop0 -o 1024 disk.img
sudo dd if=bin/bootstage2.bin of=/dev/loop0 count=1
sudo losetup -d /dev/loop0
