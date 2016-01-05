#!/bin/sh
sudo losetup /dev/loop0 -o 512 disk.img
sudo dd if=bin/bootstage1.bin of=/dev/loop0 count=1
sudo losetup -d /dev/loop0
