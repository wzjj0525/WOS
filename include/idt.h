#ifndef _IDT_H
#define _IDT_H
#include <types.h>
#define IDT_ENTRIES 256
#define KERNEL_CS 8


typedef struct {
    u16int offset_low;
    u16int sel;
    u8int always0;
    u8int flags;
    u16int offset_high;
}__attribute__((packed)) idt_entry_t;

typedef struct {
    u16int limit;
    u32int base;
}__attribute__((packed)) idt_register_t;



void set_idt_gate(u32int n, u32int handle);


void idt_init();
#endif