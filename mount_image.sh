#!/bin/bash 
sudo losetup -o 1048576 /dev/loop0 disk.img
sudo mount /dev/loop0 /mnt2
