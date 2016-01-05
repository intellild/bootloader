#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void monitor_print_hex64(uint64_t x);
void monitor_print_hex32(uint64_t x);

void hang();

#endif // MONITOR_H
