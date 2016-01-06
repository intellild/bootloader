#include "meminfo.h"
#include "print.h"
#include <stdlib.h>

void print_meminfo(meminfo_t *arr_meminfo, uint64_t nSMAP) {
  uint64_t i;

  monitor_write("|BASE              "
                "|LIMIT             "
                "|TYPE \n");

  for (i = 0; i < nSMAP; i++) {
    monitor_put(' ');
    monitor_print_hex(arr_meminfo[i].base, 64);
    monitor_put(' ');

    monitor_print_hex(arr_meminfo[i].limit, 64);
    monitor_put(' ');

    switch (arr_meminfo[i].type) {
    case 1:
      monitor_write("usable  ");
      break;
    case 2:
      monitor_write("reserved");
      break;
    case 3:
      monitor_write("ACPI rec");
      break;
    case 4:
      monitor_write("ACPI NVS");
      break;
    case 5:
      monitor_write("bad     ");
      break;
    default:
      monitor_write("unknown ");
      break;
    }
    monitor_put(' ');

    monitor_print_hex(arr_meminfo[i].acpi3, 32);
    monitor_put('\n');
  }
}
