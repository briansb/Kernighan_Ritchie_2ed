
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100     /* max size of a word */
#define BUFSIZE 100     /* max size of ungetch buffer */
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

int getword(char *, int);
int unwantedcharacter(int c);
int isalpha_underscore(int c);
int isalnum_underscore(int c);
int binsearch(char *, struct key tab[], int);
int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

/* count C keywords */
int main() {

	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF) {
		printf("Examining %s\n", word);
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
				keytab[n].count++;
				printf("\t%s is a keyword\n", word);
			}
			else {
				printf("\t%s is not a keyword\n", word);
			}
	}


	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
				keytab[n].count, keytab[n].word);

	return 0;
}

/* getword:  get next word or character from input */
/* additions:  
	1. Does not return (, ), {, }, [, ], =, ;, etc   */
int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (unwantedcharacter(c = getch()))
		;
	if (c != EOF)
		*w++ = c;

	// change isalpha to islegalstart, for alpha, num, #, ", /* ,etc.
	if (isalpha_underscore(c)) {
		/* starting a function name, keyword, or variable */
		for (; --lim > 0; w++)
		if (!isalnum_underscore(*w = getch())) {
			ungetch(*w);
			*w = '\0';
			return word[0];
		}
	} else if (c == 35) {
		/* preprocessor directive... # = 35, CR = 10 */
		while ((*w = getch()) != 10) {
			w++;
		}
		ungetch(*w);
		*w = '\0';
		return word[0];
	} else if (c == 47 ) {
		/* possible beginning of comment */
		if ((c = getch()) == 42) {
			*w++ = c;
			while ((*w = getch()) != 47) {
				w++;
			}
			*(w+1) = '\0';
			return word[0];
		}
		else {
			/* not a comment */
			ungetch(c);
		}
	} else if (c == 34) {
		/* beginning of string constant */
		while ((*w = getch()) != 34) {
			w++;
		}
		*(w+1) = '\0';
		return word[0];
	}

	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	
	*w = '\0';
	return word[0];
	
}

int isalpha_underscore(int c) {
	if (isalpha(c) || c == '_') return 1;
	else return 0;
}
int isalnum_underscore(int c) {
	if (isalnum(c) || c == '_') return 1;
	else return 0;
}
int unwantedcharacter(int c){
	//   whitespace         {           }          [          ]
	if (isspace(c) || c == 123 || c == 125 || c == 91 || c == 93 ) return 1;
	//        (          )         =          ;
	if (c == 40 || c == 41 || c == 61 || c == 59 ) return 1;
	//       +          -   
	if (c == 43 || c == 45 ) return 1;
	else return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
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