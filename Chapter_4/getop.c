#include <stdio.h>
#include <ctype.h>      /* for isdigit() */
#include "calc.h"

int getop(char s[]) {
    int i, c;
    i = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    
    /* s[0] contains the the first character */
    if (c == '-') {
        if (isdigit(s[1] = c = getch())) {
        /* found a negative number */
        i = 1;
        } else {
        /* found subtraction operator */
        ungetch(c);
        s[1] = '\0';
        return '-';
        }
    }

    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    

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