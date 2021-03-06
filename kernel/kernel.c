#include <screen.h>
#include <idt.h>
#include <isr.h>
#include <util.h>
#include <timer.h>
#include <keyboard.h>

void main () {
    screen_clean();
    char *str = "Welcome to WOS!\n";
    kprint(str);
    idt_init();
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
    kprint(">");
}



