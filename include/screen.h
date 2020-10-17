#ifndef _SCREEN_H
#define _SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define VGA_CTRL_PORT 0x3d4
#define VGA_DATA_PORT 0x3d5
#define MAX_COLS 80
#define MAX_ROWS 25
#define WHITE_IN_BLACK 0x0f

void print_char(char data, int row, int col, char attribute_byte);

void print_char_offset(char data, int offset, char attribute_byte); 
//offset:we wanna get BYTE offset NOT character offset
//but VGA IO would get cursor character offset
int get_screen_offset(int row, int col);

void screen_clean();

void print_at(char *str, int row, int col, char attribute_byte);

int get_cursor(); //return offset of cursor(byte offset)

void set_cursor(int offset);
#endif
