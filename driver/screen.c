#include <screen.h>
#include <ports.h>
#include <util.h>
void print_char(char data, int row, int col, char attribute_byte) {
    unsigned char *video_memmap = (unsigned char *) VIDEO_ADDRESS;
    int offset;
    if (row >=0 && col >=0) {
        offset = get_screen_offset(row, col);
        set_cursor(get_screen_offset(row, col));
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
    set_cursor(0);
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
void print(char *str) {
    print_at(str, -1, -1, WHITE_IN_BLACK);
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
    while (offset > (MAX_COLS * MAX_ROWS - 1)) {
        screen_scroll();
        offset -= MAX_COLS;
    }
    port_out_byte(VGA_CTRL_PORT, 14);
    port_out_byte(VGA_DATA_PORT, (offset & 0xff00) >> 8);
    port_out_byte(VGA_CTRL_PORT, 15);
    port_out_byte(VGA_DATA_PORT, offset & 0x00ff);

}

void screen_scroll() {
    int offset = get_cursor();
    for (int row = 0; row < MAX_ROWS - 1; row++) {
        mem_cpy(
                (char*)(VIDEO_ADDRESS + get_screen_offset(row + 1, 0)), 
                (char*)(VIDEO_ADDRESS + get_screen_offset(row, 0)), 
                MAX_COLS * 2
        );
    }
    fill_bottom();
    set_cursor(offset - MAX_COLS * 2);
}

void fill_bottom() {
    int row = MAX_ROWS - 1;
    int col;
    for (col = 0; col < MAX_COLS; col++) {
        *(char *)(VIDEO_ADDRESS + (row * MAX_COLS + col) * 2) = ' ';
        *(char *)(VIDEO_ADDRESS + (row * MAX_COLS + col) * 2 + 1) = WHITE_IN_BLACK;
    }
}