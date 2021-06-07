#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 1000    /* maximum input line size */
#define MAXLINES 100   /* maximum number for tail */
#define LASTLINES 10    /* default value of tail-end */


int get_line(char s[], int lim);
int atoi_ptr(char *s);
char *lineptr[MAXLINES];    /* array of pointers to text lines */
char *alloc(int);
void write_last_lines(char *lineptr[], int totallines, int last);

/* tail */
/* outputs the last n lines of input */
/* to avoid typing, use this:  ./a.out -25 < Git.txt     (or small.txt or dict.txt) */
int main(int argc, char *argv[])
{
	int len, array_counter;
	int tailend = LASTLINES;
	char line[MAXLINELENGTH];     /* current input line */
	char *p;

	while (--argc > 0) {
		tailend = -1 * atoi_ptr(*++argv);
	}
	if (tailend > MAXLINES) {
		printf("Tail end argument too big\n");
		exit(1);
	}

	array_counter = 0;
	while ((len = get_line(line, MAXLINELENGTH)) > 0) {
		/* Here's the plan....
			1.  Read in a line and assign a pointer
			2.  Keep count
			3.  When the count > tailend, shift all of the pointers by one
			4.  In this way, you just keep shifting down.  No need to store the whole thing */

		if (array_counter > MAXLINES - 1) {
			for (int i = 0; i < MAXLINES - 1; ++i) {
				lineptr[i] = lineptr[i+1];
			}
			p = malloc(len);
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[MAXLINES-1] = p;
		} else {
			p = malloc(len);    /* returns a pointer to the allocated memory */
			line[len-1] = '\0';     /* delete newline */
			strcpy(p, line);	/* copy line to p */
        	lineptr[array_counter++] = p;
		}
	}

	printf("The last %d lines are:\n", tailend);
	write_last_lines(lineptr, array_counter, tailend);
	
	return 0;
}
/* writelines:  write output lines */
void write_last_lines(char *lineptr[], int totallines, int last) 
{
	int index = totallines - last;
	if (index < 0 ) index = 0;
    for (int i = index; i < totallines; i++)
        printf("%s\n", lineptr[i]);
}
/* atoi_ptr:  convert string to integer.  Pointer version */
int atoi_ptr(char *s) {
    int n, sign;

    for ( ; isspace(*s); s++ )  /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')  /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}
/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') { s[i] = c; ++i; }
	s[i] = '\0';
	return i;
}
