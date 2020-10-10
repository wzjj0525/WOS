#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MINIX_HEADER 32

void die(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int main(int argc, char **argv) {
    int fd, i, fd2;
    char buf[1024];
    //printf("%s\n", argv[1]);
    if ((fd = open(argv[1], O_RDONLY, 0)) < 0) {
        die("Fail to open boot");
    }
    //printf("%d\n", fd);
    i = read(fd, buf, MINIX_HEADER);
    if (i != MINIX_HEADER) {
        die("NonMINIXHEADER");
    }
    i = read(fd, buf, sizeof(buf));
    if (i != 512) {
        die("Boot must be exactly 512 bytes");
    }

    if (*((unsigned short *)(buf+510)) != 0xAA55) {
        die("Boot must end at 0x55AA");
    }

    i = write(1, buf, 512);
    if (i != 512) {
        die("Fail to write Bootsect");
    }
    close(fd);
    
    if ((fd = open(argv[2], O_RDONLY, 0)) < 0) {
        die("Fail to open Setup");
    }
    i = read(fd, buf, MINIX_HEADER);
    if (i != MINIX_HEADER) {
        die("NonMINIXHEADER");
    }
    i = read(fd, buf, sizeof(buf));
    
    for (int k = i; k < 1024; k++) {
        buf[k] = '\0';
    }

    i = write(1, buf, sizeof(buf));

    close(fd);
/*
    if ((fd = open(argv[3], O_RDONLY, 0)) < 0) {
        die("Fail to open kernel");
    }
    int j;
    j = read(fd, buf, sizeof(buf));
    //printf("Kernel read %d bytes\n", j);
    i = write(1, buf, j);

    close(fd);
*/


}