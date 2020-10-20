#include <isr.h>
#include <screen.h>
#include <ports.h>
//#include <util.h>
isr_t interrupt_handle[256];
extern void int_to_ascii(int, char*);
void int_handle(registers_t regs) {

    if (regs.int_no == 13) {
        while(1){}
    }
    char str[5];
    int_to_ascii(regs.int_no, str);
    kprint(str);
    kprint("\n");
}
void set_interrupt_handle(u8int int_no, isr_t handle) {
    interrupt_handle[int_no] = handle;
}
void irq_handle(registers_t regs) {
    if (regs.int_no >= 40) {
        outb(0xa0, 0x20);
    }
    outb(0x20, 0x20);
    isr_t handle = interrupt_handle[regs.int_no];
    if (handle != 0)
        handle(regs);
}