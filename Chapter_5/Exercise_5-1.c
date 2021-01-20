#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUFSIZE 100     /* max size of ungetch buffer */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);  
void ungetch(int);
int getint(int *pn);

int main() {
    int n, array[SIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;


    for (int i = 0; i<n; i++) {
        printf("%6d%c", array[i], (i%10==9 || i==n-1) ? '\n' : ' ');
    }

    return 0;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn) {
    /* the return value of getint is EOF or 0 (not a number) or positive (valid number) */
    /*  the integer is returned by a pointer to array[n] */

    int c, sign;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        /* I don't think ungetch() should be called */
        ungetch(c);    /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
        if (c == ' ') { /* push back a + or -, then return a 0 */
                        /*   so next pass will see the operator and no space */
            ungetch( (sign == 1) ? '+' : '-'  );
            return 0;
        }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}



int getch(void) { 
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) { 
    if (bufp >= BUFSIZE)
        printf("ungetch:  too many characters\n");
    else
        buf[bufp++] = c;
}