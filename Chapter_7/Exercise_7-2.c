#include <stdio.h>
#include <string.h>

#define MAXLINE 100
#define MAXCOLUMNS 20

int main()   /* lower:  convert input to lower case */
{
    int c;
    char line[MAXLINE];
    char single_character[1];
    int column_counter = 0;

    while ((c = getchar()) != EOF) {
        if ( c <= 126 && c >= 32) { /* printable character */
            single_character[0] = c;
            strncat(line, single_character, 1);
            column_counter++;
            if (column_counter >= MAXCOLUMNS) {
                printf("%s...\n", line);
                line[0]='\0';
                column_counter = 0;
            }
        }


    }
    
    /* print last line */
    printf("%s\n", line);
    return 0;

}