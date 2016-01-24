SOURCES=stage2.o print.o meminfo.o disk.o ext3.o

CC=gcc
CFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -mno-sse -mno-sse2 -mno-mmx -Os
LDFLAGS=-Tlink.ld

all: $(SOURCES) link

clean:
	-rm *.o ../../bin/bootstage2.bin

link:
	ld $(LDFLAGS) -o ../../bin/bootstage2.bin $(SOURCES)
