#include "meminfo.h"
#include "print.h"

void print_meminfo(uint64_t nSMAP)
{
    uint64_t i;
    meminfo_t *arr_meminfo = (meminfo_t*)0x1000;
    //memcpy(arr_meminfo, (void*)0x1000, nSMAP);

    monitor_write("BASE              |LIMIT             |TYPE\n");
    for(i = 0;i < nSMAP;i++)
    {
        monitor_print_hex64(arr_meminfo[i].base);
        monitor_put(' ');
        monitor_print_hex64(arr_meminfo[i].limit);
        monitor_put(' ');
        monitor_print_hex32(arr_meminfo[i].type);
        monitor_put(' ');
        monitor_print_hex32(arr_meminfo[i].acpi3);
        monitor_put('\n');
    }
}
