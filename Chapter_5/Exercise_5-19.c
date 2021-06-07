
#include <stdio.h>
#include <string.h> /* for strcpy, strcat, isalpha, isalnum */
#include <ctype.h>  /* for strcpy, strcat, isalpha, isalnum */

#define MAXTOKEN 100
#define BUFSIZE 100     /* max size of ungetch buffer */

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char out[1000];             /* output string */

int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
void remove_redundant_parentheses(char a[]);

/* undcl:  convert word descriptions to declarations */
int main() {
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		// check for enclosing parentheses after the type
		remove_redundant_parentheses(out);
		printf("%s\n", out);
	}
	return 0;
}
void remove_redundant_parentheses(char a[]) {
	int length = strlen(a);
	int i = 0;

	// check for first character after type...return if not left paren
	while (!isspace(a[i++]));
	if (a[i] != 40) return;

	// check for last character...return if not right paren
	if (a[length - 1] != 41) return;

	// check for next to last character...return if left paren
	if (a[length - 2] == 40) return;

	// remove parens
	while (a[i] != '\0') {
		a[i] = a[i+1];
		i++;
	}
	a[i - 2] = '\0';
	
	return;
}
int gettoken(void) {        /* return next token */
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
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