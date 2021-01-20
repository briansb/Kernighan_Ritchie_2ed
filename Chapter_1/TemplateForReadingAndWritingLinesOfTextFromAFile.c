#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int get_line_from_file(char s[], int lim, FILE *fptr);

int main() {

    int len;
	char line[MAXLINE];     /* current input line */

    /* input file */
    FILE *input_file;
    input_file = fopen("text_in.txt", "r");
    if (!input_file) {
        printf("Could not open file\n"); 
        return 1;
    }
    /* output file */
    FILE *output_file;
    output_file = fopen("text_out.txt", "w");

    while ((len = get_line_from_file(line, MAXLINE, input_file)) > 0) {
		printf("%s", line);
        fprintf(output_file,"%s", line);

	}
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}

/* get_line_from_file:  read a line into s, return length */
int get_line_from_file(char s[], int lim, FILE *fptr) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getc(fptr)) != EOF && c != '\n'; ++i) s[i] = c;
	/* added increment postfix increment operator...pg 47 */
	if (c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}