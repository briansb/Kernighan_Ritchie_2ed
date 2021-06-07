#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 1024

int getchar_v1(void);
int getchar_v2(void);

int main() {
    int c;
    // while ( (c=getchar_v1()) != EOF ) 
    //     printf("%c", c);

    while ( (c=getchar_v2()) != EOF ) 
        printf("%c", c);

    return 0;

}

/* getchar:  unbuffered single character input */
int getchar_v1(void) {
    char c;
    return ( read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

/* getchar:  simple buffered version */
int getchar_v2(void) {
    static char buf[BUFSIZE];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {   /* buffer is empty */
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    
    /* returns one character, increments buf, decrements n */
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}