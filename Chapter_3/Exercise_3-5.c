#include <stdio.h>
#include <string.h>

/* itob:  convert n to base b as characters in s */
void itob(int n, char s[], int b);
char digit_to_character(int d);
void reverse(char s[]);

int main() {
    char s[100];
    char c;
    int i;
    
    int n;
    int b;

    printf ("Enter a number: ");
    while (scanf("%d", &n) != EOF) {
        printf("Enter a base: ");
        scanf("%d", &b);
        printf("Numerical value = %d\n", n);
        itob(n, s, b);
        i = 0;
        printf("String value = ");
        while ((c = s[i++]) != '\0') printf("%c", c);
        printf("\n");
        printf ("Enter a number: ");
    } 

    return 0;
}
/* itob:  convert n to base b as characters in s */
void itob(int n, char s[], int b) {
    int digit;
    int i = 0;
    while (n != 0) {
        digit = n % b;
        s[i] = digit_to_character(digit);
        n /= b;
        i++;
    }
    s[i] = '\0';
    reverse(s);
    return;
}
char digit_to_character(int d) {
    if ( d >= 0 && d <= 9) return '0' + d;
    else return 87 + d;
}
/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
    return;
}