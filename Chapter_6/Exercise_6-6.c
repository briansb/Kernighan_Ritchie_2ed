#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100     /* max size of a word */
#define HASHSIZE 100

struct nlist {              /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text - definition */
};

static struct nlist *hashtab[HASHSIZE];     /* pointer table */
char *strdup_bb(char *);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int getline_bb(char s[], int lim);
struct nlist *install(char *name, char *defn);
void replace(char * o_string, char * s_string, char * r_string);

/* count C keywords */
int main() {

	int c, len, i;
	char line[MAXWORD];
	char name[MAXWORD];
	char defn[MAXWORD];
	
	char newline[MAXWORD];
	char *ret;
	int found;

	while ((len = getline_bb(line, MAXWORD)) > 0) {
		found = 0;
		/* check for #define as part of line */
		ret = strstr(line, "#define");
		if ( ret != NULL ) {
			found = 1;
			//printf("Found #define\n");
			/* extract info, add to lookup table, don't print line */
			char *name_ptr = name;
			char *defn_ptr = defn;
			i = 7;
			while ( isspace(line[i++])   ) ;
			i--;
			while ( !isspace(line[i])  ) {
				*name_ptr = line[i];
				name_ptr++;
				i++;
			}
			*name_ptr = '\0';
			while ( isspace(line[i++])   ) ;
			i--;
			while ( !isspace(line[i])  ) {
				*defn_ptr = line[i];
				defn_ptr++;
				i++;
			}
			*defn_ptr = '\0';
			//printf("Name = %s, Definition = %s\n", name, defn);
			install(name, defn);
		} 
		/* check for line with lookup table entry */
		else {
			/* found a lookup table entry in line - do swap, print newline */
			struct nlist *ptr;
			char *ret = NULL;
			for (int i = 0; i < HASHSIZE; i++) {
				ptr = hashtab[i];
				while (ptr != NULL) {
					ret = strstr(line, ptr->name);
					if (ret != NULL) {
						found = 1;
						//printf("Found %s in %s\n", ptr->name, line);
						replace(line, ptr->name, ptr->defn);
						printf("%s\n", line);
						break;
					}
					ptr = ptr->next;
				}
			}
			//if (ret == NULL) printf("%s", line);
		}
		if (found == 0) printf("%s", line);
	}

	

	return 0;
}

/* get_line:  read a line into s, return length */
int getline_bb(char s[], int lim) {
    int c, i;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
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
void replace(char * o_string, char * s_string, char * r_string) {
      //a buffer variable to do all replace things
      char buffer[MAXWORD];
      //to store the pointer returned from strstr
      char * ch;
 
      //first exit condition
      if(!(ch = strstr(o_string, s_string)))
              return;
 
      //copy all the content to buffer before the first occurrence of the search string
      strncpy(buffer, o_string, ch-o_string);
 
      //prepare the buffer for appending by adding a null to the end of it
      buffer[ch-o_string] = 0;
 
      //append using sprintf function
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
 
      //empty o_string for copying
      o_string[0] = 0;
      strcpy(o_string, buffer);
      //pass recursively to replace other occurrences
      return replace(o_string, s_string, r_string);
 }