#include <stdio.h>
#define MAXLINE 100   /* maximum input line size */

int get_line(char s[], int lim);
void squeeze_v2(char s1[], char s2[]);

int main()  
{
	int len;
	char line1[MAXLINE];
    char line2[MAXLINE];

    printf("Enter line to be squeezed\n");
	while ((len = get_line(line1, MAXLINE)) > 0) {
        printf("Enter characters to be removed\n");
        len = get_line(line2, MAXLINE);
        squeeze_v2(line1, line2);
        printf("New line = %s\n", line1);
        printf("Enter line to be squeezed\n");
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
/* remove all occurrences of characters in s2 from string s1 */
void squeeze_v2(char s1[], char s2[]) {
    int i, j, k;
    char c;
    int len = 0;
    while (s2[len] != '\n') len++;
    for (i = j = k = 0; s1[i] != '\0'; i++) {
        while (  ((c = s2[k++]) != s1[i])   &&  c != '\n'  ) { ; }
        if (k > len) {
            /* nothing found, continue */
            k = 0;
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
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
