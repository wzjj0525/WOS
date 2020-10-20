#include <isr.h>
#include <screen.h>
//#include <util.h>
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