#!/bin/bash
sudo losetup /dev/loop0 disk.img
sudo dd if=bin/bootsector.bin of=/dev/loop0 bs=440 count=1
sudo losetup -d /dev/loop0
