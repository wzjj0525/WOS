#include <screen.h>
void main () {
    screen_clean();
    //print_at("Welcome to WOS!\nThis is a message whitout BIOS.\n", 0, 0, WHITE_IN_BLACK);
    //set_cursor(8);
    set_cursor(get_screen_offset(24, 79));
    int o = get_cursor();
    print_at("Welcome to WOS!\nThis is a message without BIOS.\n", -1, -1, WHITE_IN_BLACK);
}