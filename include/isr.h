#ifndef _ISR_H
#define _ISR_H
#include <types.h>
typedef struct registers
{
   u32int ds;                  // Data segment selector
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   u32int int_no, err_code;    // Interrupt number and error code (if applicable)
   u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} __attribute__((packed)) registers_t;

void int_handle(registers_t regs);

#endif