SOURCES=stage2.o print.o meminfo.o disk.o

CC=clang
CFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -mno-sse -mno-sse2 -mno-mmx -O3
LDFLAGS=-Tlink.ld
AS=nasm
ASFLAGS=-felf64

all: $(SOURCES) link

clean:
	-rm *.o ../../bin/bootstage2.bin

link:
	ld $(LDFLAGS) -o ../../bin/bootstage2.bin $(SOURCES)
