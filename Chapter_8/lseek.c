#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 1024

char buf[BUFSIZE];

long lseek(int fd, long offset, int origin);
int get(int fd, long pos, char *buf, int n);

int main() {
    int fd1;
    fd1 = open("a.txt", O_RDONLY, 0);
    get(fd1, 10, buf, 3);
    printf("%s\n", buf);

    close(fd1);
    return 0;
}

/* get:  read n bytes from position pos */
int get(int fd, long pos, char *buf, int n) {
    if (lseek(fd, pos, 0) >= 0)  /* get to pos */
        return read(fd, buf, n);
    else
        return -1;
}