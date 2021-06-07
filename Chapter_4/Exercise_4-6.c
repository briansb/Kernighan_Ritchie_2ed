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
#include <math.h>       /* for sin, exp, and pow */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of val stack */
#define MAXOP   100     /* max size of operand or operator */
#define BUFSIZE 100     /* max size of ungetch buffer */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
double variable[28];    /* array of twenty six variables plus dummy plus most recently printed value */

void push (double f);   /* push value onto stack */
double pop(void);       /* pop and return value from stack */
int getop(char s[]);    /* getop: get next operator or numeric operand */
int getch(void);        /* get a (possibly pushed back) character */
void ungetch(int);      /* push character back on input */
void print_top_of_stack();      /* print top of stack */
void duplicate_top_of_stack();  /* duplicate top of stack */
void swap_top_two();            /* swap top two elements of stack */


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
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("error:  zero modulo\n");
                break;
            case '!':               /* print top of stack */
                print_top_of_stack();
                break;
            case '@':               /* duplicate top of stack */
                duplicate_top_of_stack();
                break;
            case '#':               /* swap top two elements of stack */
                swap_top_two();
                break;
            case '$':               /* clear stack */
                sp = 0;
                break;
            case '&':               /* sine(x) */
                push(sin(pop()));
                break;
            case '^':               /* exp(x) */
                push(exp(pop()));
                break;
            case '~':               /* pow(x,y) x^y */
                op2 = pop();
                push(pow(op2, pop()));
                break;
            case '<':               /* store variable */
                /*   variable[getop(s) - ascii_value_for_a] = top of stack
                     so, after <, must input a through z.  Find index of letter a = 0, z = 26
                     then, store top of stack (do not pop) into variable[index]   */
                variable[getop(s) - 97] = val[sp-1];
                break;
            case '>':               /* recall variable */
                /*   retrieve variable from -> variable[getop(s) - ascii_value_for_a]
                     then place on top of stack for subsequent operation    */
                op2 = variable[getop(s) - 97];
                push(op2);
                break;
            case '\n':
                /* store the most recently printed value */
                variable[27] = val[sp-1];
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
void print_top_of_stack() {
    int sp_temp = sp;
    if (sp_temp > 0)
        printf("top of stack = %.8g\n", val[sp_temp-1]);
    else {
        printf("print top of stack error:  stack empty\n");
    }
}
void duplicate_top_of_stack() {
    int sp_temp = sp;
    if (sp_temp > 0)
        push(val[sp_temp-1]);
    else {
        printf("duplicate top of stack error:  stack empty\n");
    }
}
void swap_top_two() {
    int sp_temp = sp;
    double temp1, temp2;
    if (sp_temp > 1) {
        temp1 = pop();
        temp2 = pop();
        push(temp1);
        push(temp2);
    }
    else {
        printf("swap_top_two error:  stack does not contain two values\n");
    }
}