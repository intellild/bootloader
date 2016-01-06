#include "disk.h"
#include "common.h"
#include "print.h"

void get_dpt_info(dpt_t *dpt) {
  uint8_t parinfo[16];
  int i;

  for (i = 0; i < 4; i++) {
    memcpy(parinfo, (void *)((uint64_t)0x7C00 + 446 + i * 16), 16);
    if (parinfo[0] == 0x80) {
      dpt[i].active = true;
    }
    dpt[i].indHeadBeg = parinfo[1];
    dpt[i].indCylinderBeg = parinfo[2] & 0x3F;
    dpt[i].indSectorBeg =
        (((uint16_t)parinfo[2] & 0xC0) << 2) + (uint16_t)parinfo[3];
    dpt[i].type = parinfo[4];
    dpt[i].indHeadEnd = parinfo[5];
    dpt[i].indCylinderEnd = parinfo[6] & 0x3F;
    dpt[i].indSectorEnd =
        (((uint16_t)parinfo[6] & 0xC0) << 2) + (uint16_t)parinfo[7];
    dpt[i].used = *((uint32_t *)&parinfo[8]);
    dpt[i].total = *((uint32_t *)&parinfo[2]);
  }
}

void print_dpt(dpt_t *dpt) {
  int i;
  for (i = 0; i < 4; i++) {
    if (dpt[i].type != 0) {
    }
  }
}
