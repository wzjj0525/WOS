#include <util.h>
//#include <string.h>
void mem_cpy(char* source, char* dest, int bytes) {
    int i = 0;
    for (i = 0; i < bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void int_to_ascii(u32int num, char* str) {
    int i = 0;
    while(1) {
        str[i++] = num % 10 + 48;
        num /= 10;
        if (!num) break;
    }
    str[i] = '\0';

}