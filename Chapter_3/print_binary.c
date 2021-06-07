#include <stdio.h>
#include <limits.h>
#include <string.h>

void shortint_binarystring(short int n, int size, char s[]);
void int_binarystring(int n, int size, char s[]);
void word_size();
void reverse(char s[]);

int main() {
    /* run this for reference...need to know word size to print in binary */
    //word_size();
    /*  for this machine.....
    char = 8 bits
        -128 -> 127 ---- 255
    short int = 16 bits
        -32768 -> 32767 ---- 65535
    int = 32 bits
        -2,147,483,648 -> 2,147,483,647 ---- 4,294,967,295
    long int = 64 bits
        -9,223,372,036,854,775,808 -> 9,223,372,036,854,775,807 ---- 18,446,744,073,709,551,615
    long long int = 64 bits
        same as above
    */

    char s[65];
    
    //short int n;
    //int size = 16;
    int n;
    int size = 32;
    printf ("Enter a number: ");
    //while (scanf("%hd", &n) != EOF) {
    while (scanf("%d", &n) != EOF) {
        //printf("Decimal value = %hd\n", n);
        printf("Decimal value = %d\n", n);
        //shortint_binarystring(n, size, s);
        int_binarystring(n, size, s);
        for (int i = 0; i < size; i++) printf("%c", s[i]);
        printf("\n");
        printf ("Enter a number: ");
    } 

    return 0;
}
void int_binarystring(int n, int size, char s[]) {
    for (int i = 0; i < size; ++i, n >>= 1) {
        s[i] =  (n & 1) ? '1' : '0';
    }
    s[size] = '\0';
    reverse(s);
    return;
}
void shortint_binarystring(short int n, int size, char s[]) {
    for (int i = 0; i < size; ++i, n >>= 1) {
        s[i] =  (n & 1) ? '1' : '0';
    }
    s[size] = '\0';
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
/* get various word sizes for this machine */
void word_size() {
    int number_of_bits = 0;
    unsigned char i = UCHAR_MAX;
    while (i != 0) { i /= 2; number_of_bits++; }
    printf("char word size = %d bits\n", number_of_bits);
    number_of_bits = 0;
    unsigned short int j = USHRT_MAX;
    while (j != 0) { j /= 2; number_of_bits++; }
    printf("short int word size = %d bits\n", number_of_bits);
    number_of_bits = 0;
    unsigned int k = UINT_MAX;
    while (k != 0) { k /= 2; number_of_bits++; }
    printf("int word size = %d bits\n", number_of_bits);
    number_of_bits = 0;
    unsigned long int l = ULONG_MAX;
    while (l != 0) { l /= 2; number_of_bits++; }
    printf("long int word size = %d bits\n", number_of_bits);
    number_of_bits = 0;
    unsigned long long int m = ULLONG_MAX;
    while (m != 0) { m /= 2; number_of_bits++; }
    printf("long long int word size = %d bits\n", number_of_bits);
}