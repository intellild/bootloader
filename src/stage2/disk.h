#ifndef DISK_H
#define DISK_H

#include <inttypes.h>

typedef struct {
  uint8_t active;
  uint8_t indHeadBeg;
  uint16_t indCylinderBeg;
  uint8_t indSectorBeg;
  uint8_t indHeadEnd;
  uint16_t indCylinderEnd;
  uint8_t indSectorEnd;
  uint8_t type;
  uint32_t used;
  uint32_t total;
} dpt_t;

void get_dpt_info(dpt_t *dpt);
void print_dpt(dpt_t *dpt);

#endif
