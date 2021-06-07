#include <stdio.h>
#include <stdarg.h>

int var_length_to_routine(int count, ...);
void var_length_from_routine(int count, ...);

int main() {
    
    int a = 3;
    int b = 4;
    int c = 5;
    printf("Sum = %d\n", var_length_to_routine(3, a, b, c));
    var_length_from_routine(3,&a,&b,&c);
    printf("a = %d, b = %d, c = %d\n", a,b,c);
    return 0;
}

/* var_length_from_routine:  variable-length argument list from a subroutine - values change */
void var_length_from_routine(int count, ...)
{
    //int *val;
    va_list ap;
    int i = 987;

    va_start(ap, count);
    for(i = 0; i < count; i++) {
       int *val = va_arg(ap, int*);
       *val = i;
    }
    va_end(ap);
 
    return;
}

/* var_length_to_routine:  variable-length argument list to a subroutine */
int var_length_to_routine(int count, ...)
{
    int val = 0;
    va_list ap;
    int i;

    va_start(ap, count);
    for(i = 0; i < count; i++) {
       val += va_arg(ap, int);
    }
    va_end(ap);
 
    return val;
}