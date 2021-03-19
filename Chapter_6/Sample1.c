#include <stdio.h>

/* replace multiple blanks with one blank */
int main() {
	
    int c ;
    char *one_two = "stringconstant";
    long _var = 23;
    
    while ((c = getchar()) != EOF) {
        while (c == 32) {
            putchar(c);
            while ((c = getchar()) == 32) // 32 = blank
                ;
        }
        putchar(c);
    }


}