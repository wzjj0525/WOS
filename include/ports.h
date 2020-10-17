#ifndef _PORTS_H
#define _PORTS_H
void port_out_byte(unsigned short port, unsigned char data);

void port_out_word(unsigned short port, unsigned short data);

unsigned char port_in_byte(unsigned short port);

unsigned short port_in_word(unsigned short port);
#endif