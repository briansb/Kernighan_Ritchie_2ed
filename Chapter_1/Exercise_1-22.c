#include <stdio.h>
#define MAXLINE 40   /* maximum input line size...should be 1000 or so */
#define WRAP 10      /* fold length...should be 40 of greater */
#define BLANK 32     /* ASCII blank character */
#define TAB 9        /* ASCII tab character */

int get_line(char s[], int lim);
int cut_chunk(char s[], int num_chars, char x[]);
int line_length(char s[]);
void copy_chunk(char s[], char x[]);
void insert_chunk(char s[], char x[]);

/* read a line of input, and displays on console.  Wraps the text at the specified column */
/* can handle very long input lines...much greater than MAXLINE */
int main()
{
	int index, len;
	char line[MAXLINE + WRAP];     /* current input line - size increase due to need for buffering */
	char chunk[WRAP+1];     /* WRAP length plus \0 */
	int cut_chars;			/* the number of beginning characters to remove from the line */
	int NeedHyphen;         /* hyphenation indicator */

	//printf("01234567890123456789012345678901234567890\n");  /* very useful for debugging */
	chunk[0] = '\0';
	while ((len = get_line(line, MAXLINE)) > 0) {
		// must insert previous last segment into new line (may be empty)
		insert_chunk(line, chunk);

		while (line_length(line) > WRAP) {
			NeedHyphen = 0;
			index = WRAP - 1;
			while (line[index] != BLANK && line[index] != TAB && index >= 0) {
					--index;
				}
			if (index == -1) { /* no blanks or tabs */
				index = WRAP -1;
				NeedHyphen = 1;
			}

			cut_chars = index + 1;
			cut_chunk(line, cut_chars, chunk);
			if (NeedHyphen) { printf("%s-\n", chunk); } 
			else { printf("%s\n", chunk); }
		}

		// if original line > MAXLINE, there will be no \n
		//  and the rest of the line has been buffered
		if ( line[line_length(line)-1] != '\n') {
			// must save the last segment for insertion into rest of buffer
			copy_chunk(line, chunk);
		} else {
			chunk[0] = '\0';
			printf("%s (the last segment)\n", line);
		}
	}
	return 0;
}

void insert_chunk(char s[], char x[]) {
	int offset = line_length(x);
	if (offset == 0) return;
	for (int i = line_length(s); i >= 0; --i) {
		s[i+offset] = s[i];
	}
	for (int i = 0; i < offset; ++i) {
		s[i] = x[i];
	}
	return;
}

void copy_chunk(char s[], char x[]) {
	int i = 0;
	while (s[i] != '\0') { 
		x[i] = s[i];
		++i;
	}
	x[i] = '\0';
	return;
}

int line_length(char s[]) {
	int i = 0;
	while (s[i] != '\0') ++i;
	return i;
}

/* cut_chunk: returns the first num_chars characters...\n, \t, etc PLUS \0 */
/* return value is actual number of characters cut plus \0 */
/* s[] is shifted so that s[0] is the next character not in chunk[] */
int cut_chunk(char s[], int num_chars, char x[]) {
	int i, cut_num;
	for (i = 0; i < num_chars; ++i) {
		x[i] = s[i];
		if (x[i] == '\0') {
			s[0] = '\0';
			return i+1;
		}
	}
	x[i] = '\0';
	cut_num = i+1;
	// shift s[]
	i = 0;
	while (s[i+num_chars] != '\0') {
		s[i] = s[i+num_chars];
		++i;
	}
	s[i] = '\0';
	return cut_num;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') { s[i] = c; ++i; }
	s[i] = '\0';
	return i;
}
