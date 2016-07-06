#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>

static inline void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %1, %0"
                 :
                 : "dN"(port), "a"(value));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "dN"(port));
    return ret;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
                 : "=a"(ret)
                 : "dN"(port));
    return ret;
}

static inline void memcpy(void* dst, void* src, uint64_t len)
{
    uint64_t i;
    for (i = 0; i < len; i++)
    {
        ((char*)dst)[i] = ((char*)src)[i];
    }
}

static inline void memset(void* dst, char val, uint64_t len)
{
    uint64_t i;
    for (i = 0; i < len; i++)
    {
        ((char*)dst)[i] = val;
    }
}

static inline uint32_t power(uint32_t base, uint32_t exp)
{
    uint32_t ret = 1;
    uint32_t i;
    for (i = 0; i < exp; i++)
    {
        ret *= base;
    }
    return ret;
}

static inline int32_t strequ(char* str1, char* str2, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

static inline void hang()
{
    while (1)
        ;
}

#endif
