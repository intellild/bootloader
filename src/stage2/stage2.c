#include "common.h"
#include "disk.h"
#include "ext2.h"
#include "meminfo.h"
#include "print.h"

static dpt_t dpt[4];
static uint64_t nSMAP;

void stage2()
{

    asm volatile("movq %%r8,%0"
                 : "=r"(nSMAP)::);
    meminfo_t meminfo[nSMAP];
    memcpy(meminfo, (void*)0x1000, sizeof(meminfo_t) * nSMAP);
    monitor_init();

    monitor_write("reached bootstage2\n");
#ifndef NODEBUG
    monitor_write("MEMORY INFO:\n");
    print_meminfo(meminfo, nSMAP);
#endif

    get_dpt_info(dpt);
#ifndef NODEBUG
    print_dpt(dpt);
#endif

    if (ext2_verify_disk(&dpt[0]))
    {
        monitor_write("detected ext2 file system\n");
        ext2_read(&dpt[0], "kernel", (void*)0x100000);
    }

    hang();
}
