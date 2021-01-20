#include <stdio.h>

/* replace multiple blanks with one blank */
int main() {
	
    int c ;
    
    
    while ((c = getchar()) != EOF) {
        while (c == 32) {
            putchar(c);
            while ((c = getchar()) == 32) // 32 = blank
                ;
        }
        putchar(c);
    }


}
