#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER 0
#define OPERATION 1
#define STACKLIMIT 100

/* determine_type:  determines if char string is an operation or number */
int determine_type(char *ptr[]);
/* atof:  convert string s to double */
double atod(char s[]);

/* stack items */
double stack[STACKLIMIT];
double *stackptr;
void push(double d);
double pop(void);

/* expr:  evaulates RPN expressions from command line arguments */
/* e.g., ./expr 8 14 + 2 / will return 11 */
/* NOTE: To pass * (asterisk), must escape it....  ./expr 8 14 \*  */
int main(int argc, char *argv[])
{
    stackptr = stack;
    double op2;
    while (--argc > 0) {
        switch (determine_type(++argv)) {
            case NUMBER:
                //printf("%s is a number\n", *argv);
                push(atod(*argv));
                break;
            case OPERATION:
                //printf("%s is an operation\n", *argv);
                switch (*argv[0]) {
                    case '+':
                        push(pop() + pop());
                        break;
                    case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                    case '*':
                        push(pop() * pop());
                        break;
                    case '/':
                        op2 = pop();
                        push(pop() / op2);
                        break;
                }
                break;
            default:
                printf("%s is not recognized\n", *argv);
                break;
                
        }
    }
    
    printf("Top of stack = %.8g\n", pop());
    
    return 0;
}
int determine_type(char *ptr[]) {
    //printf("determine_type received %s\n", *ptr);
    // 42 = *, 43 = +, 45 = -, 47 = /
    //ptr points to a character string, so we must access the first char
    if (strlen(*ptr) == 1 && (*ptr[0] == 42 || *ptr[0] == 43 || *ptr[0] == 45 || *ptr[0] == 47)) {
        return OPERATION;   
    }

    // this is used so that ptr is not changed
    char *index = *ptr;
    // /* 48 - 57, ASCII digits, 45 = -, 46 = .  */
    int c;
    while(c = *index++)    /* walks through multiple-character arguments */
        if ((c >= 48 && c <= 57) || c == 45 || c == 46) {
            ;
        } else {
            return -1;
        }
    
    return NUMBER;
}


// no error checking
double pop(void) {
    return *--stackptr;
}

// no error checking
void push(double d) {
    *stackptr++ = d;
    return;
}

double atod(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)   /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
