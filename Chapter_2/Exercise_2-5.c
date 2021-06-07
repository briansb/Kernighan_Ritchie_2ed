#include <stdio.h>
#define MAXLINE 100   /* maximum input line size */

int get_line(char s[], int lim);
int any(char s1[], char s2[]);

int main()  
{
	int len;
	char line1[MAXLINE];
    char line2[MAXLINE];

    printf("Enter string to be searched\n");
	while ((len = get_line(line1, MAXLINE)) > 0) {
        printf("Enter string to be found\n");
        len = get_line(line2, MAXLINE);
        printf("Location of first occurrence = %d\n", any(line1, line2));
        printf("Enter line to be searched\n");
	}

	return 0;
}

/* find the first occurrence in s1 of any character in s2 */
int any(char s1[], char s2[]) {
    int i = 0;
    int j = 0;
    char c, d;
    int len = 0;
    while (s2[len] != '\n') len++;
    while ( (c = s1[i++]) != '\n') {
        while ( ((d = s2[j++]) != '\n') && d != c ) { ; }
        if (j <= len) return i-1;
        j = 0;
    }
    return -1;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}
