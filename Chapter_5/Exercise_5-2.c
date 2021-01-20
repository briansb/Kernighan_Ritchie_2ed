#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUFSIZE 100     /* max size of ungetch buffer */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void);  
void ungetch(int);
int getfloat(float *pn);

int main() {
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;


    for (int i = 0; i<n; i++) {
        printf("%.4f%c", array[i], (i%10==9 || i==n-1) ? '\n' : ' ');
    }

    return 0;
}
    
/* getfloat:  get next float from input into *pn */
int getfloat(float *pn) {
    /* the return value of getfloat is EOF or 0 (not a number) or positive (valid number) */
    /*  the integer is returned by a pointer to array[n] */

    int c, sign;
    float factor = 10.0;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
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

    /* get leading digits, if any */
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    /* get decimal point, if any */
    if (c == '.') 
        c = getch();

    /* get trailing digits...same routine as above, but now use / instead of * */
    while (isdigit(c)) {
        *pn = *pn + (c - '0')/factor;
        factor *= 10.0; 
        c = getch();
    }

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