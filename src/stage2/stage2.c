#include "common.h"
#include "meminfo.h"
#include "disk.h"
#include "ext2.h"
#include "print.h"

static dpt_t dpt[4];
static uint64_t nSMAP;

void __Start()
{
    asm volatile("movq %%r8,%0"
                 : "=r"(nSMAP)::);
    meminfo_t meminfo[nSMAP];
    memcpy(meminfo, (void*)0x1000, sizeof(meminfo_t) * nSMAP);

    monitor_clear();
    monitor_write("reached bootstage2\n");

#ifndef NODEBUG
    monitor_write("MEMORY INFO:\n");
    print_meminfo(meminfo, nSMAP);
#endif

    get_dpt_info(dpt);
#ifndef NODEBUG
    print_dpt(dpt);
#endif

    hang();
}
