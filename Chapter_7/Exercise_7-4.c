#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

int main() {
    int i;
    double f;
    char s[10];

    minscanf("%d %f %s", &i, &f, &s);

    printf("i = %d, f = %lf, s = %s\n", i, f, s);
    return 0;
}

/* minscanff:  minimal scanff with variable argument list */
void minscanf(char *fmt, ...) 
{
    va_list ap;    /* points to each unnamed arg in turn */
    char *p, *sval;
    int *ival;
    double *dval;


    va_start(ap, fmt);  /* make ap point to first unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            //putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double*);
                scanf("%lf", dval);
                break;
            case 's':
                sval = va_arg(ap, char*);
                scanf("%s", sval);
                break;
            default:
                putchar(*p);
                break;
            }
    }
    va_end(ap);     /* clean up */
}