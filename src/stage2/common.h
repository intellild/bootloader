#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>

#ifndef bool
#define bool uint8_t
#define true 1
#define false 0
#endif

static inline void outb(uint16_t port, uint8_t value) {
  asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

static inline uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

static inline void memcpy(void *dst, void *src, uint64_t len) {
  uint64_t i;
  for (i = 0; i < len; i++) {
    ((char *)dst)[i] = ((char *)src)[i];
  }
}

static inline void memset(void *dst, char val, uint64_t len) {
  uint64_t i;
  for (i = 0; i < len; i++) {
    ((char *)dst)[i] = val;
  }
}

static inline void hang() {
  while (1)
    ;
}

#endif
