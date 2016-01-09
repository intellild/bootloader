#ifndef DISK_H
#define DISK_H

#include <inttypes.h>
#include "common.h"

typedef struct {
  uint8_t active;
  uint32_t lbaBeg;
  uint32_t lbaEnd;
  uint8_t type;
  uint32_t used;
  uint32_t total;
} dpt_t;

void get_dpt_info(dpt_t *dpt);
void print_dpt(dpt_t *dpt);
void read_disk(void *buf, uint32_t lba, uint8_t cntSector);

void disk_reset(void);
bool disk_rdy(void);

static inline void io_wait(void) {
  asm volatile("jmp 1f\n\t"
               "1:jmp 2f\n\t"
               "2:");
}

#endif
