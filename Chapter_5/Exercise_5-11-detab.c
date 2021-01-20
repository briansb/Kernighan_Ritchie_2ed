#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8       /* tab stop every 8th column */
#define TAB 9           /* ASCII value of tab */
#define SPACE 32        /* ASCII value of space */
#define UNDERLINE 95   /* ASCII value of underline, used for debugging */

int get_line(char s[], int lim);
int GetNextTabStop(int column, int argc, char *argv[]);
int atoi_ptr(char *s);
void AddSpaces(char line[], int n, int spaces);

/* detab, see Exercise 1-20*/
/* replace tab characters with spaces */
/*  tab stops are specified as command line arguments.  If there are more
        tab stops (in the input line) than arguments, use the default value of 8 */
int main(int argc, char *argv[])
{
	int len, i, index, spaces, next_tab_stop;
	char line[MAXLINE];     /* current input line */
	char outline[MAXLINE];    /* transformed line */

	printf("01234567t9012345t7890123t5678901t3456789t1234567t9012345t7890123t5678901t3456789t\n");
	while ((len = get_line(line, MAXLINE)) > 0) {
		index = 0;  /* the column number of the new output line */
		for (i=0; i<len; ++i) {
			if (line[i] == TAB) {
				/* compute number of spaces to get to next tab stop */
				next_tab_stop = GetNextTabStop(index, argc, argv);
				spaces = next_tab_stop - index;
				AddSpaces(outline, index, spaces);
				index = next_tab_stop;
			} else {
				outline[index] = line[i];
				++index;
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
		/* line[i] = UNDERLINE; */
		line[i] = SPACE;
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