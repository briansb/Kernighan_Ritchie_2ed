#include <stdio.h>
#define MAXLINE 100   /* maximum input line size */

int get_line(char s[], int lim);
void squeeze(char s[], int c);

int main()
{
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
        squeeze(line, 't');
		printf("%s", line);
	}

	return 0;
}

/* remove all occurrences of character c from string s */
void squeeze(char s[], int c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
    return;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}
