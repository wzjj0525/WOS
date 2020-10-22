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

int get_screen_offset(int row, int col);
void screen_clean();
void print_at(char *str, int row, int col, char attribute_byte);
void kprint(char *str);
void kprint_backspace();
int get_cursor(); 
void set_cursor(int offset);
void screen_scroll();
void fill_bottom();

#endif
