#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear(void);

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void monitor_print_hex(uint64_t x, uint8_t bits);

void hang(void);

#endif // MONITOR_H
