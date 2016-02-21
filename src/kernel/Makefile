SOURCES=kernel.o

CC=clang
CXX=clang++
CFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -mno-sse -mno-sse2 -mno-mmx -O3
CXXFLAGS=-ffreestanding -Wall -Wextra -fno-exceptions -mno-sse -mno-sse2 -mno-mmx -O3
LDFLAGS=-Tlink.ld

all: $(SOURCES) link

clean:
	-rm *.o ../../bin/kernel

link:
	ld $(LDFLAGS) -o ../../bin/kernel $(SOURCES)
