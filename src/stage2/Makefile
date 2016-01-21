SOURCES=stage2.o print.o meminfo.o disk.o ext3.o

CC=clang
CFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -mno-sse -mno-sse2 -mno-mmx -Os -DDEBUG
LDFLAGS=-Tlink.ld

all: $(SOURCES) link

clean:
	-rm *.o ../../bin/bootstage2.bin

link:
	ld $(LDFLAGS) -o ../../bin/bootstage2.bin $(SOURCES)
