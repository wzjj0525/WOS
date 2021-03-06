#ifndef _ISR_H
#define _ISR_H
#define IRQ(x) ((x)+(32))
#include <types.h>
typedef struct registers
{
   u32int ds;                  // Data segment selector
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   u32int int_no, err_code;    // Interrupt number and error code (if applicable)
   u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} __attribute__((packed)) registers_t;

void int_handle(registers_t regs);
void irq_handle(registers_t regs);
typedef void (*isr_t)(registers_t);
void set_interrupt_handle(u8int int_no, isr_t handle);
#endif