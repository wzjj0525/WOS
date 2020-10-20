#ifndef _PORTS_H
#define _PORTS_H
void outb(unsigned short port, unsigned char data);

void outw(unsigned short port, unsigned short data);

unsigned char inb(unsigned short port);

unsigned short inw(unsigned short port);
#endif