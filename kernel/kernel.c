#include <screen.h>
#include <idt.h>
#include <isr.h>
#include <util.h>

void main () {
    screen_clean();
    kprint("Welcome to WOS!\n");
    idt_init();
}