#include "print.h"
#include "common.h"
#include "meminfo.h"
#include "disk.h"

static dpt_t dpt[4];
static uint64_t nSMAP;

void __Start() {
  asm volatile("movq %%r8,%0" : "=r"(nSMAP)::);
  meminfo_t meminfo[nSMAP];

  memset(dpt, 0, sizeof(dpt_t) * 4);
  memcpy(meminfo, (void *)0x1000, sizeof(meminfo_t) * nSMAP);

  monitor_clear();
  monitor_write("reached bootstage2\n\n");

  monitor_write("MEMORY INFO:\n");
  print_meminfo(meminfo, nSMAP);

  get_dpt_info(dpt);
  print_dpt(dpt);

  char buf[512];
  read_disk(buf, 2048, 1);

  hang();
}
