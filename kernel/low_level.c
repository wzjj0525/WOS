#include <low_level.h>
void port_out_byte(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a"(data) , "d"(port));
}
void port_out_word(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a"(data) , "d"(port));
}
unsigned char port_in_byte(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}
unsigned short port_in_word(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
    return result;
}