#!/bin/bash
cd src
cd bootloader
nasm -o bootsector.bin bootsector.s
nasm -o bootloader.bin bootloader.s
cd ..

