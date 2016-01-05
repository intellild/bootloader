#include "print.h"
#include "common.h"
#include "meminfo.h"

void __Start()
{
    uint64_t nSMAP = 0;
    asm volatile("movq %%r8,%0":"=r"(nSMAP)::);

    meminfo_t meminfo[nSMAP];
    memcpy(meminfo, (void*)0x1000, sizeof(meminfo_t)*nSMAP);

    monitor_clear();
    monitor_write("reached bootstage2\n");

    monitor_write("nSMAP= ");
    monitor_print_hex64(nSMAP);
    monitor_put('\n');
    monitor_put('\n');

    print_meminfo(meminfo, nSMAP);

    hang();
}
