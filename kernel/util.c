#include <util.h>

void mem_cpy(char* source, char* dest, int bytes) {
    int i = 0;
    for (i = 0; i < bytes; i++) {
        *(dest + i) = *(source + i);
    }
}