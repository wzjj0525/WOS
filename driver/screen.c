#include <screen.h>
#include <low_level.h>
void print_char(char data, int row, int col, char attribute_byte) {
    unsigned char *video_memmap = (unsigned char *) VIDEO_ADDRESS;
    int offset;
    if (row >=0 && col >=0) {
        offset = get_screen_offset(row, col);
    }
    else {
        offset = get_cursor();
    }
    if (data == '\n') {
        offset = get_screen_offset((offset / 2 / 80), 79);
    }
    video_memmap[offset] = data;
    video_memmap[offset + 1] = attribute_byte;
    set_cursor(offset + 2);
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
    int offset;
    if (row >=0 && col >=0) {
        offset = get_screen_offset(row, col);
    } 
    else {
        offset = get_cursor();
    }
    int i = 0;
    set_cursor(offset);
    while (str[i] != 0) {
        print_char(str[i++], -1, -1, attribute_byte);
    }
}

int get_cursor() {
    port_out_byte(VGA_CTRL_PORT, 14);
    int offset = port_in_byte(VGA_DATA_PORT) << 8;
    port_out_byte(VGA_CTRL_PORT, 15);
    offset += port_in_byte(VGA_DATA_PORT);

    offset *= 2;
    return offset;
}

void set_cursor(int offset) {
    offset /= 2;
    port_out_byte(VGA_CTRL_PORT, 14);
    port_out_byte(VGA_DATA_PORT, (offset & 0xff00) >> 8);
    port_out_byte(VGA_CTRL_PORT, 15);
    port_out_byte(VGA_DATA_PORT, offset & 0x00ff);
}