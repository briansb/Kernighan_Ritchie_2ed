#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
#define TABSTOP 8       /* tab stop every 8th column */
#define TAB 9           /* ASCII value of tab */
#define SPACE 32        /* ASCII value of space */
#define UNDERLINE  95   /* ASCII value of underline, used for debugging */

int get_line(char s[], int lim);
int GetNextTabStop(int column);
void AddSpaces(char line[], int n, int spaces);

/* detab */
/* replace tab characters with spaces */
int main()
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
				next_tab_stop = GetNextTabStop(index);
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

void AddSpaces(char line[], int n, int spaces) {
	int i;
	for (i=n; i<n+spaces; ++i) {
		line[i] = SPACE;
	}
	return;
}

int GetNextTabStop(int col) {
	/* assumes evenly spaced tab stops */
	int n = col / TABSTOP;
	/* printf("For column %d, next tab stop is %d\n", col, (n+1) * TABSTOP); */
	return (n+1) * TABSTOP;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') { s[i] = c; ++i; }
	s[i] = '\0';
	return i;
}
