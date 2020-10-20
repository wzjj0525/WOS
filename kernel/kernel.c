#include <screen.h>
#include <idt.h>
#include <isr.h>
#include <util.h>

void main () {
    screen_clean();
    print_char('W', 0, 0, WHITE_IN_BLACK);
    char *str = "Welcome to WOS!\n";
    kprint(str);
    //idt_init();
    //__asm__ __volatile__("int $3");
}