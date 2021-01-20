#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8       /* tab stop every 8th column */
#define BLANK 32        /* ASCII value for blank */
#define TAB 9			/* ASCII value for tab */
#define UNDERLINE 95   /* ASCII value of underline, used for debugging */


int get_line(char s[], int lim);
int GetNextTabStop(int column, int argc, char *argv[]);
void AddSpaces(char line[], int n, int spaces);
int atoi_ptr(char *s);

/* entab */
/* replaces blanks with tabs and spaces */
int main(int argc, char *argv[])
{
	int len, i, index, spaces, beginning_column, pad;
	char line[MAXLINE];     /* current input line */
	char outline[MAXLINE];    /* transformed line */

	printf("01234567t9012345t7890123t5678901t3456789t1234567t9012345t7890123t5678901t3456789t\n");
	while ((len = get_line(line, MAXLINE)) > 0) {
		index = 0;  /* the column number of the new output line */
		spaces = 0; /* current number of blanks between words */
		beginning_column = 0;
		int column_index;
		for (i=0; i<len; ++i) {
			if (line[i] != BLANK) {
				if ( spaces ) {
					if (spaces == 1) outline[index++] = BLANK;  /* just write the space and move on */
					else {
						//printf("Found %d spaces at column %d\n", spaces, beginning_column);
						/* How many tab stops exist between spaces? */
						column_index = beginning_column;
						while (GetNextTabStop(column_index, argc, argv) < beginning_column + spaces) {
							//printf("\tFound tab stop at %d\n", GetNextTabStop(column_index));
							outline[index++] = TAB;
							column_index = GetNextTabStop(column_index, argc, argv);
						}
						pad = i - column_index;
						AddSpaces(outline, index, pad);
						index += pad;
					}
					spaces = 0;
					beginning_column = 0;
				}

				outline[index] = line[i];
				++index;
			} else {
				if ( !beginning_column) beginning_column = i;
				++spaces;
			}

		}
		outline[index] = '\0';
		printf("%s", outline);
		printf("01234567t9012345t7890123t5678901t3456789t1234567t9012345t7890123t5678901t3456789t\n");
	}
	return 0;
}
int GetNextTabStop(int col, int argc, char *argv[]) {
	int argcol;
	int temp = 0;
	while (--argc > 0) {
		argcol = atoi_ptr(*++argv);
		if (col < argcol && col >= temp) {
			printf("Args:  For column %d, next tab stop is %d\n", col, argcol);
			return argcol;
		}
		temp = argcol;
	}
	
	/* default tab stop spacing */
	int n = col / TABSTOP;
	printf("DEFAULT:  For column %d, next tab stop is %d\n", col, (n+1) * TABSTOP);
	return (n+1) * TABSTOP;
}

void AddSpaces(char line[], int n, int spaces) {
	int i;
	for (i=n; i<n+spaces; ++i) {
		line[i] = BLANK;
	}
	return;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') { s[i] = c; ++i; }
	s[i] = '\0';
	return i;
}
/* atoi_ptr:  convert string to integer.  Pointer version */
int atoi_ptr(char *s) {
    int n, sign;

    for ( ; isspace(*s); s++ )  /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')  /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}