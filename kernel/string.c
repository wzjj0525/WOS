#include <types.h>
#include <string.h>

int strlen(char *s) {
    int i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

void reverse(char *s, int len) {
    char c;
    for (int i = 0; i < len / 2; i++) {
        c = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = c;
    }
}
void append(char* str, char c) {
    int len = strlen(str);
    str[len] = c;
    str[len+1] = '\0';
}
int strcmp(char* s1, char* s2) {
    int i = 0;
    while (1) {
        if (s1[i] == 0 && s2[i] == 0)
            return 0;
        else if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        i++;
    }
}