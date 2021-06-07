#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct nlist {              /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text - definition */
};

#define HASHSIZE 11
#define MAXWORD 100

static struct nlist *hashtab[HASHSIZE];     /* pointer table */
char *strdup_bb(char *);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);


int main() {
    
    if (install("one", "1") == NULL) printf("Name/Definition installation failed\n");
    if (install("two","2") == NULL) printf("Name/Definition installation failed\n");
	if (install("three", "3") == NULL) printf("Name/Definition installation failed\n");
	if (install("four", "4") == NULL) printf("Name/Definition installation failed\n");
	if (install("five", "5") == NULL) printf("Name/Definition installation failed\n");
	if (install("six", "6") == NULL) printf("Name/Definition installation failed\n");
	if (install("seven", "7") == NULL) printf("Name/Definition installation failed\n");
	if (install("eight", "8") == NULL) printf("Name/Definition installation failed\n");
	if (install("nine", "9") == NULL) printf("Name/Definition installation failed\n");
	if (install("ten", "10") == NULL) printf("Name/Definition installation failed\n");
    if (install("eleven", "11") == NULL) printf("Name/Definition installation failed\n");
    if (install("twelve", "12") == NULL) printf("Name/Definition installation failed\n");
    if (install("thirteen", "13") == NULL) printf("Name/Definition installation failed\n");

    struct nlist *ptr;
	if (install("two", "2222") == NULL) printf("Name/Definition installation failed\n");

    if ((ptr = lookup("nine")) != NULL) printf("Found %s and %s\n", ptr->name, ptr->defn);
    else printf("Did not find name\n");

    return 0;
}

/* hash:  form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}
/* lookup:  look for s in hashtab (hash table) */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;     /* found */
    return NULL;       /* not found */
}
/* install:  put (name, defn) in hashtab (hash table) */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {      /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup_bb(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];  /* if duplicate hash value, the new name/defn pair is inserted AT THE BEGINNING */
        hashtab[hashval] = np;        /* the new block points the existing list, and hashtab[hashval] now points to the news name/defn pair */
    } else            /* already there */
        free((void *) np->defn);
    if ((np->defn = strdup_bb(defn)) == NULL)
        return NULL;
    return np;
}
/* stdrdup: make a duplicate of s */
char *strdup_bb(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
