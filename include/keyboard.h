#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <isr.h>
#define SC_MAX 57
#define BACKSPACE 0x0E
#define ENTER 0x1C
void keyboard_callback(registers_t regs);

void init_keyboard();

void print_letter(u8int scancode);
#endif