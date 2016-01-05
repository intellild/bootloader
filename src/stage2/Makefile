SOURCES=boot.o stage2.o common.o print.o meminfo.o

CC=clang
CFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS=-Tlink.ld
AS=nasm
ASFLAGS=-felf64

all: $(SOURCES) link

clean:
	-rm *.o ../../bin/bootstage2.bin

link:
	ld $(LDFLAGS) -o ../../bin/bootstage2.bin $(SOURCES)
