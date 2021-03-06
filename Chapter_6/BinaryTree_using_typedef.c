#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100     /* max size of ungetch buffer */

typedef struct tnode *Treeptr;

typedef struct tnode {              /* the tree node */
    char *word;             /* points to the text */
    int count;              /* number of occurrences */
    Treeptr left;     /* left child */
    Treeptr right;    /* right child */
} Treenode;

Treeptr addtree(Treeptr, char *);
Treeptr talloc(void);      /* for addtree */
char *strdup_bb(char *);
void treeprint(Treeptr);

int getword(char *, int);
int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */


/* word frequency count */
int main() {
    Treeptr root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    treeprint(root);
    return 0;
}

/*addtree:  add a node with w, at or below p */
Treeptr addtree(Treeptr p, char *w) {
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup_bb(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;         /* repeated word */
    else if (cond < 0)      /* less than into left subtree */
        p->left = addtree(p->left,w);
    else                    /* greater than into right subtree */
        p->right = addtree(p->right,w);
    return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(Treeptr p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s \n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc:  make a node */
Treeptr talloc(void) {
    return (Treeptr)malloc(sizeof(Treenode));
}

/* stdrdup: make a duplicate of s */
char *strdup_bb(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* getword:  get next word of character from input */
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