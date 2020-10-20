#include <stdio.h>

int main() {

    for (int i = 0;i < 16; i++) {
        printf("[global irq%d]\n", i);
    }
}