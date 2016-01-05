#include "common.h"

void hang()
{
    while(1)
    {
        
    }
}

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void memcpy(void *dst, void *src, uint64_t len)
{
    uint64_t i;
    for(i = 0;i < len;i++)
    {
        ((char*)dst)[i] = ((char*)src)[i];
    }
}
