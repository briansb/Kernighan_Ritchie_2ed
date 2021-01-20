#include <stdio.h>

/* replace tab, backspace, backslash with escape characters */
/* NOTE:  I can't make the backspace detection work */
int main() {
	
    int c ;
    int backslash = 92;
    while ((c = getchar()) != EOF) {
        if (c == '\b') {
            putchar(backslash);
            c = 'b';
        }
        if (c == '\t') {
            putchar(backslash);
            c = 't';
        }
        if (c == '\\') {
            putchar(backslash);
            putchar(backslash);
        }
        putchar(c);
    }


}
