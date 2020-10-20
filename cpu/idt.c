#include <idt.h>
#include <isr.h>
idt_entry_t idt[IDT_ENTRIES];
idt_register_t idt_reg;
extern void int32(registers_t regs);
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


void set_idt_gate(u32int n, u32int handle) {
    idt[n].offset_low = (handle & 0x0000ffff);
    idt[n].offset_high = (handle & 0xffff0000) >> 16;
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8e;
}

void idt_init() {
    set_idt_gate(0, (u32int)isr0);
    set_idt_gate(1, (u32int)isr1);
    set_idt_gate(2, (u32int)isr2);
    set_idt_gate(3, (u32int)isr3);
    set_idt_gate(4, (u32int)isr4);
    set_idt_gate(5, (u32int)isr5);
    set_idt_gate(6, (u32int)isr6);
    set_idt_gate(7, (u32int)isr7);
    set_idt_gate(8, (u32int)isr8);
    set_idt_gate(9, (u32int)isr9);
    set_idt_gate(10, (u32int)isr10);
    set_idt_gate(11, (u32int)isr11);
    set_idt_gate(12, (u32int)isr12);
    set_idt_gate(13, (u32int)isr13);
    set_idt_gate(14, (u32int)isr14);
    set_idt_gate(15, (u32int)isr15);
    set_idt_gate(16, (u32int)isr16);
    set_idt_gate(17, (u32int)isr17);
    set_idt_gate(18, (u32int)isr18);
    set_idt_gate(19, (u32int)isr19);
    set_idt_gate(20, (u32int)isr20);
    set_idt_gate(21, (u32int)isr21);
    set_idt_gate(22, (u32int)isr22);
    set_idt_gate(23, (u32int)isr23);
    set_idt_gate(24, (u32int)isr24);
    set_idt_gate(25, (u32int)isr25);
    set_idt_gate(26, (u32int)isr26);
    set_idt_gate(27, (u32int)isr27);
    set_idt_gate(28, (u32int)isr28);
    set_idt_gate(29, (u32int)isr29);
    set_idt_gate(30, (u32int)isr30);
    set_idt_gate(31, (u32int)isr31);

    /*outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);*/

    set_idt_gate(32, (u32int)irq0);
    set_idt_gate(33, (u32int)irq1);
    set_idt_gate(34, (u32int)irq2);
    set_idt_gate(35, (u32int)irq3);
    set_idt_gate(36, (u32int)irq4);
    set_idt_gate(37, (u32int)irq5);
    set_idt_gate(38, (u32int)irq6);
    set_idt_gate(39, (u32int)irq7);
    set_idt_gate(40, (u32int)irq8);
    set_idt_gate(41, (u32int)irq9);
    set_idt_gate(42, (u32int)irq10);
    set_idt_gate(43, (u32int)irq11);
    set_idt_gate(44, (u32int)irq12);
    set_idt_gate(45, (u32int)irq13);
    set_idt_gate(46, (u32int)irq14);
    set_idt_gate(47, (u32int)irq15);

    set_interrupt_handle(32, int32);

    idt_reg.base =(u32int) (&idt);
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;
    
    __asm__ volatile("lidt %0" : : "m"(idt_reg));
}