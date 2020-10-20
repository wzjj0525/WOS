#include <screen.h>
#include <idt.h>
#include <isr.h>
#include <util.h>

void main () {
    screen_clean();
    char *str = "Welcome to WOS!\n";
    kprint(str);
    idt_init();
    __asm__ __volatile__("int $32");
}