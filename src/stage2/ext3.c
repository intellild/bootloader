#include "ext3.h"
#include "disk.h"
#include "common.h"

bool ext3_verify_partition(dpt_t dpt) {
  uint8_t buf[512];
  read_disk(buf, dpt.lbaBeg + 2, 1);
}
