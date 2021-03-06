#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000     /* max size of a word */
#define BUFSIZE 1000     /* max size of ungetch buffer */

int line_number = 1;
int getword(char *, int);
int unwantedcharacter(int c);
int isalpha_underscore(int c);
int isalnum_underscore(int c);
int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */


struct tnode {              /* the tree node */
    char *word;             /* points to the text */
    int count;              /* number of occurrences */
	int line_numbers[BUFSIZE];  /* array of line numbers */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);      /* for addtree */
char *strdup_bb(char *);
void treeprint(struct tnode *);


/* cross-reference */
int main() {
	
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;

	while (getword(word, MAXWORD) != EOF) {
		//printf("Examining %s\n", word);
		if (isalpha(word[0]))
			root = addtree(root, word);
	}

	/* print tree */
	treeprint(root);

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
	/* track the line number */
	if (c == 10) line_number++;
	//   whitespace         {           }          [          ]
	if (isspace(c) || c == 123 || c == 125 || c == 91 || c == 93 ) return 1;
	//        (          )         =          ;
	if (c == 40 || c == 41 || c == 61 || c == 59 ) return 1;
	//       +          -   
	if (c == 43 || c == 45 ) return 1;
	else return 0;
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

/*addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup_bb(w);
        p->count = 1;
		p->line_numbers[p->count-1] = line_number;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;         /* repeated word */
		p->line_numbers[p->count-1] = line_number;
	}
    else if (cond < 0)      /* less than into left subtree */
        p->left = addtree(p->left,w);
    else                    /* greater than into right subtree */
        p->right = addtree(p->right,w);
    return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s - ", p->word);
		for (int i = 0; i < p->count; i++) printf("%d ", p->line_numbers[i]);
		printf("\n");
        treeprint(p->right);
    }
}

/* talloc:  make a node */
struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* stdrdup: make a duplicate of s */
char *strdup_bb(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}