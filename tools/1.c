#include <stdio.h>

int main() {

    for (int i = 0;i < 32; i++) {
        printf("    set_idt_gate(%d, (u32int)isr%d);\n", i, i);
    }
}