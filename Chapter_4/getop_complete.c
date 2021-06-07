#include <stdio.h>
#include <ctype.h>

#define MAXOP   100     /* max size of operand or operator */
#define BUFSIZE 100     /* max size of ungetch buffer */
#define NUMBER  '0'     /* signal that number was found */

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);        /* getop: get next operator or numeric operand */
void ungetch(int);      /* get a (possibly pushed back) character */
int getop(char s[]);    /* push character back on input */

int main () {
    char s[MAXOP];
    int type;

    while ((type = getop(s)) != EOF) {
        printf("Type = %d\n", type);
    }

    return 0;
}
/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
/* get a (possibly pushed back) character */
int getch(void) {       
    return (bufp > 0) ? buf[--bufp] : getchar();
}
/* push character back on input */
void ungetch(int c) {   
    if (bufp >= BUFSIZE)
        printf("ungetch:  too many characters\n");
    else
        buf[bufp++] = c;
}