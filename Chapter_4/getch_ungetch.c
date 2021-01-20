#include <stdio.h>

#define BUFSIZE 100     /* max size of ungetch buffer */

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);
void ungetch(int);

int main () {
    int c;

    c = getch();
    printf("getch() returned %c, with bufp = %d\n", c, bufp);
    c = getch();
    printf("getch() returned %c, with bufp = %d\n", c, bufp);
    c = getch();
    printf("getch() returned %c, with bufp = %d\n", c, bufp);
    c = getch();
    printf("getch() returned %c, with bufp = %d\n", c, bufp);

    ungetch(c);
    printf("ungetch(c) called with c = %c, and bufp = %d\n", c, bufp);
    c = 91;
    ungetch(c);
    printf("ungetch(c) called with c = %c, and bufp = %d\n", c, bufp);
    
    c = getch();
    printf("getch() returned %c, with bufp = %d\n", c, bufp);



    return 0;
}
int getch(void) {       /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {   /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch:  too many characters\n");
    else
        buf[bufp++] = c;
}
