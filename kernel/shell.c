#include <types.h>
#include <keyboard.h>
#include <string.h>
#include <shell.h>
#include <screen.h>
char key_buffer[256];
int key_len = 0;
char *SC_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
char SC_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
void shell_input(u8int scancode) {
    char sc_ascii = SC_ascii[scancode];
    if (scancode == BACKSPACE) {
        if (key_len) {
            kprint_backspace();
            key_len--;
        }
        else {}
    }
    else if (scancode == ENTER) {
        kprint("\n");
        if (key_len) {
            key_buffer[key_len] = '\0';
            deal_with_input(key_buffer);
            key_buffer[0] = '\0';
            key_len = 0;
        }
        kprint(">");
    }
    else {
        char output[2]={sc_ascii, '\0'};
        append(key_buffer, SC_ascii[scancode]);
        kprint(output);
        key_len++;
    }
}
void deal_with_input(char* key_buffer) {
    if (strcmp(key_buffer, "QUIT") == 0)
        asm volatile("hlt");
    kprint(key_buffer);
    kprint("\n");
}