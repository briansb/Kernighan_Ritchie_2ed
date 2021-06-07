/*  Structure of program
    while (next operator or operand is not EOF)
        if (number)
            push it
        else if (operator)
            pop operands
            do operation
            push result
        else if (newline)
            pop and print top of stack
        else
            error
*/

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <ctype.h>      /* for isdigit() */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of val stack */
#define MAXOP   100     /* max size of operand or operator */
#define BUFSIZE 100     /* max size of ungetch buffer */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */


void push (double f);   /* push value onto stack */
double pop(void);       /* pop and return value from stack */
int getop(char s[]);    /* push character back on input */
int getch(void);        /* getop: get next operator or numeric operand */
void ungetch(int);      /* get a (possibly pushed back) character */


/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':                /* subtraction and division are not commutative */
                op2 = pop();         /*  so the order matters */
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error:  zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error:  unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

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
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:  stack full, can't push %g\n", f);
}
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error:  stack empty\n");
        return 0.0;
    }
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