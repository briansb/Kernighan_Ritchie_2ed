#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main()   /* lower:  convert input to lower case */
{
    int c;
    char line[MAXLINE];
    char single_character[1];

    while ((c = getchar()) != EOF) {
        if ( c <= 126 && c >= 32) { /* printable character */
            single_character[0] = c;
            strncat(line, single_character, 1);
            
        }


    }
    
    /* print last line */
    printf("%s\n", line);
    return 0;

}