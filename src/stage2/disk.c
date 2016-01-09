#include "disk.h"
#include "common.h"
#include "print.h"

#define DISK_STAT_ERR(stat) (stat & 0x1)
#define DISK_STAT_DRQ(stat) (stat & 0x8)
#define DISK_STAT_SRV(stat) (stat & 0x10)
#define DISK_STAT_DFE(stat) (stat & 0x20)
#define DISK_STAT_RDY(stat) (stat & 0x40)
#define DISK_STAT_BSY(stat) (stat & 0x80)

#define DISK_STAT inb(0x1F7)

void get_dpt_info(dpt_t *dpt) {
  uint8_t parinfo[16];
  int i;
  for (i = 0; i < 4; i++) {
    memcpy(parinfo, (void *)((uint64_t)0x7C00 + 446 + i * 16), 16);
    if (parinfo[0] == 0x80) {
      dpt[i].active = true;
    }

    dpt[i].lbaBeg += parinfo[1] * 63 * 255;
    dpt[i].lbaBeg += (parinfo[2] & 0x3F) * 63;
    dpt[i].lbaBeg +=
        (((uint16_t)parinfo[2] & 0xC0) << 2) + (uint16_t)parinfo[3] - 1;

    dpt[i].type = parinfo[4];

    dpt[i].lbaEnd += parinfo[5] * 63 * 255;
    dpt[i].lbaEnd += (parinfo[6] & 0x3F) * 63;
    dpt[i].lbaEnd +=
        (((uint16_t)parinfo[6] & 0xC0) << 2) + (uint16_t)parinfo[7] - 1;

    dpt[i].used = *((uint32_t *)&parinfo[8]);
    dpt[i].total = *((uint32_t *)&parinfo[2]);
  }
}

void print_dpt(dpt_t *dpt) {
  int i;
  for (i = 0; i < 4; i++) {
    if (dpt[i].)
      monitor_write("partition ");
    monitor_print_hex(i, 8);
    monitor_write(":\n");
    monitor_write(" BEG: ");
    monitor_print_hex(dpt[i].lbaBeg, 32);
    monitor_write(" END: ");
    monitor_print_hex(dpt[i].lbaEnd, 32);
    monitor_put('\n');
  }
}

void read_disk(void *buf, uint32_t lba, uint8_t cntSector) {
  if (!disk_rdy()) {
    disk_reset();
  }

  outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
  outb(0x1F2, cntSector);
  outb(0x1F3, (uint8_t)lba);
  outb(0x1F4, (uint8_t)(lba >> 8));
  outb(0x1F5, (uint8_t)(lba >> 16));
  outb(0x1F7, 0x20);

  int i = 0;
  int stat = inb(0x1F7);
  while (DISK_STAT_BSY(stat)) {
    i++;
    if (i >= 4) {
      monitor_write("disk error 1\n");
      hang();
    }
    if (DISK_STAT_DRQ(stat)) {
      break;
    }
    stat = DISK_STAT;
  }

  for (i = 0; i < cntSector; i++) {
    int j;
    for (j = 0; j < 256; j++) {
      ((uint16_t *)buf)[i * 256 + j] = inw(0x1F0);
    }
    io_wait();
    stat = DISK_STAT;
    while (DISK_STAT_BSY(stat)) {
      stat = DISK_STAT;
    }
    if (DISK_STAT_ERR(stat)) {
      monitor_write("disk error 2\n");
      hang();
    }
  }
}

void disk_reset(void) {
  outb(0x1F7, 0x4);
  outb(0x1F7, 0);

  int i;
  for (i = 0; i < 4; i++) {
    inb(0x1F7);
  }

  while (!disk_rdy())
    ;
}

bool disk_rdy(void) {
  uint8_t stat;
  stat = inb(0x1F7);
  return !DISK_STAT_BSY(stat) && DISK_STAT_RDY(stat);
}
