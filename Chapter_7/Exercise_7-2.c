#include <stdio.h>
#include <string.h>

#define MAXLINE 100
#define MAXCOLUMNS 20

int get_hex_from_int(char *, int);

int main()   /* lower:  convert input to lower case */
{
    int c;
    char line[MAXLINE];
    char single_character[1];
    char hex_char[4];
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
        } else {
            get_hex_from_int(hex_char,c);
            strncat(line, hex_char, 4);
            column_counter += 4;
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
int get_hex_from_int(char *hex_char, int c) {
	char *w = hex_char;

	*w = '#';
    w++;
    /* left digit */
    *w = (c / 16) + 48;
    w++;
    /* right digit */
    if ((c % 16) < 10 ) *w = (c % 16) + 48;
    else *w = (c % 16) + 87;
    w++;
    *w = '#';

	return hex_char[0];
}