#ifndef _TIMER_H
#define _TIMER_H
#define TIMER_FREQUENCY 1193180
#include <isr.h>
void init_timer(u32int);

void timer_callback(registers_t regs);
#endif