#include <stdio.h>

int lower(int c);

int main() {

    char letter = 'D';
    printf("The lowercase of %c is %c\n", letter, lower(letter));
    letter = 'c';
    printf("The lowercase of %c is %c\n", letter, lower(letter));
    
   return 0;
}
/* Only works for ASCII character set */
int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c+'a' - 'A' : c;
}