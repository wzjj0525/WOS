#include "screen.h"
void print_char(char data, int row, int col, char attribute_byte) {
    unsigned char *video_memmap = (unsigned char *) VIDEO_ADDRESS;
    int offset;
    offset = get_screen_offset(row, col);
    video_memmap[offset] = data;
    video_memmap[offset + 1] = attribute_byte;
    return ;
}

void print_char_offset(char data, int offset, char attribute_byte) {
    unsigned char *video_memmap = (unsigned char *) VIDEO_ADDRESS;
    video_memmap[offset] = data;
    video_memmap[offset + 1] = attribute_byte;
    return ;
}

int get_screen_offset(int row, int col) {
    return (row * MAX_COLS + col) * 2;
}

void screen_clean() {
    for (int i = 0; i < MAX_ROWS; i++)
        for (int j = 0; j < MAX_COLS; j++)
            print_char(' ', i, j, WHITE_IN_BLACK);
}

void print_at(char *str, int row, int col, char attribute_byte) {
    int offset = get_screen_offset(row, col);
    int i = 0;
    while (str[i] != 0) {
        print_char_offset(str[i++], offset, attribute_byte);
        offset += 2;
    }
}