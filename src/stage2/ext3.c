#include "ext3.h"
#include "disk.h"
#include "common.h"

static uint8_t buf[512];

bool ext3_verify_partition(dpt_t dpt) {
  ext3_super_block_t *psuperblock = (ext3_super_block_t *)buf;
  read_disk(buf, dpt.lbaBeg + 2, 2);

  if (psuperblock->signature != 0xEF53) {
    return false;
  }

  return true;
}
