#include <stdio.h>
#define MAXLINE 20   /* maximum input line size */

int get_line(char s[], int lim);

/* read a line of input, and display on console */
int main()
{
	int len;
	char line[MAXLINE];     /* current input line */

	while ((len = get_line(line, MAXLINE)) > 0) {
		printf("%s", line);
	}

	return 0;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	/* added increment postfix increment operator...pg 47 */
	if (c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}
