#ifndef MEMINFO_H
#define MEMINFO_H

#include <inttypes.h>

typedef struct {
  uint64_t base;
  uint64_t limit;
  uint32_t type;
  uint32_t acpi3;
} meminfo_t;

void print_meminfo(meminfo_t *arr_meminfo, uint64_t nSMAP);

#endif
