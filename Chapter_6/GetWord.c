#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100     /* max size of a word */
#define BUFSIZE 100     /* max size of ungetch buffer */

int getword(char *, int);
int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

/* count C keywords */
int main() {

	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF) {
		//if (isalpha(word[0]))
		printf("%s",word);
	}

	return 0;
}


/* getword:  get next word or character from input */
int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
int getch(void) {       /* get a (possibly pushed back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {   /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch:  too many characters\n");
	else
		buf[bufp++] = c;
}