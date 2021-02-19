
#include <stdio.h>
#include <string.h> /* for strcpy, strcat, isalpha, isalnum */
#include <ctype.h>  /* for strcpy, strcat, isalpha, isalnum */

#define MAXTOKEN 100
#define BUFSIZE 100     /* max size of ungetch buffer */

enum { NAME, PARENS, BRACKETS, ARGS };

int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int gettoken(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

void dcl(void);
void dirdcl(void);

/* dcl:  convert declarations to words */
int main() {
	while (gettoken() != EOF) {     /* 1st token on line */
		strcpy(datatype, token);    /* is the datatype */
		out[0] = '\0';
		dcl();     /* parse rest of line */
		if (tokentype != '\n') {
			printf("main error:  syntax error\n");
			// clear input buffer
			while (getch() != '\n') {}
			bufp = 0;
		}
		printf("%s:  %s %s\n", name, out, datatype);
	}
	return 0;
}


/* dirdcl:  parse a direct declarator */
void dirdcl(void) {
	int type;
	if (tokentype == '(') {     /* ( dcl ) */
		dcl();
		// if (tokentype != ')')
		// 	printf("dirdcl error:  missing )\n");
	}
	else if (tokentype == NAME)   /* variable name */
		strcpy(name, token);
	else
		printf("dirdcl error:  expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS || type == ARGS)
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == ARGS) {
			strcat(out, " function(");
			strcat(out, token);
			strcat(out, ") returning");
		}
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}

}
/* dcl:  parse a declarator */
void dcl(void) {
	int ns;
	for (ns = 0; gettoken() == '*';)  /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}


int gettoken(void) {        /* return next token */
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t') /* ignore blanks */
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else if (isalpha(c)) {
			for (*p++ = c; isalnum(c = getch()); )
				*p++ = c;
			*p = '\0';
			return tokentype = ARGS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == ')') {
		/* end of arguments */
		return tokentype = '(';
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