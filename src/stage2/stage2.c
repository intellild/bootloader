#include "print.h"
#include "common.h"
#include "meminfo.h"
#include "disk.h"

static dpt_t dpt[4];
static uint64_t nSMAP;

void __Start() {
  asm volatile("movq %%r8,%0" : "=r"(nSMAP)::);
  meminfo_t meminfo[nSMAP];
  memcpy(meminfo, (void *)0x1000, sizeof(meminfo_t) * nSMAP);

  monitor_clear();
  monitor_write("reached bootstage2\n\n");

  monitor_write("MEMORY INFO:\n");
  print_meminfo(meminfo, nSMAP);

  get_dpt_info(dpt);
  print_dpt(dpt);
  
  hang();
}
