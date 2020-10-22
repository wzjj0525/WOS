#include <keyboard.h>
#include <isr.h>
#include <screen.h>
#include <ports.h>
#include <types.h>
#include <util.h>
#include <shell.h>
extern void user_input(char*);

void keyboard_callback(registers_t regs) {
    u8int scancode = inb(0x60);
    //scancode = 2;
    if (scancode > SC_MAX) {
        return ;
    }
    shell_input(scancode);
}

void init_keyboard() {
    set_interrupt_handle(IRQ(1), keyboard_callback);
}

