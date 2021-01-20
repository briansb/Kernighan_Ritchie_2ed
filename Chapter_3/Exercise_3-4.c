#include <stdio.h>
#include <string.h>


/* itoa:  convert n to characters in s */
//void itoa(short int n, char s[]);
void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    char s[100];
    char c;
    int i;

    /* for any wordsize N, the range of signed integers is
       -2^(N-1) to 2^(N-1)-1...for a 4-bit word, the range is -8 to 7.
       So, you can negate any number from -7 to 7.  You can't negate -8 since you can't represent 8.
       If you try, it just returns -8 */
    
    int n;

    printf ("Enter a number: ");
    while (scanf("%d", &n) != EOF) {
        printf("Numerical value = %d\n", n);
        itoa(n, s);
        i = 0;
        printf("String value = ");
        while ((c = s[i++]) != '\0') printf("%c", c);
        printf("\n");
        printf ("Enter a number: ");
    } 

    return 0;
}
/* itoa:  convert n to characters in s */
//void itoa(short int n, char s[]) {
void itoa(int n, char s[]) {
    int i, sign;
    int cornercase = 0;
    //short int n_previous = n;
    int n_previous = n;

    if ((sign = n) < 0)    /* record sign */
        n = -n;            /* and make n positive */

    /* check for special case of minvalue of data type */
    if ( n == n_previous) {
        cornercase = 1;
        n--;  /* decrement it to the biggest positive number */
    }

    i = 0;
    do {                   /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    if (cornercase) s[0] += 1;  /* now add the one back...since the trailing digit will never be a 9, we can get away with this */
    reverse(s);
    return;
}
/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
    return;
}