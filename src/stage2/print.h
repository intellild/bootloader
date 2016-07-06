#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

void monitor_put(char c);

void monitor_clear(void);

void monitor_write(char *c);

void monitor_print_hex(uint64_t x, uint8_t bits);

void monitor_init();

#endif // MONITOR_H
