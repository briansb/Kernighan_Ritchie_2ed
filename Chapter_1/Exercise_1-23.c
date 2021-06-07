#include <stdio.h>

#define MAXLINE 200
#define SPACE 32
#define RETURN 10
#define SLASH 47
#define ASTERISK 42

int get_line_from_file(char s[], int lim, FILE * file) ;
int LeftCommentCharacters(char s[], FILE * input_file);
int RightCommentCharacters(char s[], FILE * input_file);
int WhiteSpace(char c);

/* remove comments and blank lines from C program */
/* since you're removing all the comments, might as well remove blank lines */
/* I cheated by adding input and output file capability, 
     mainly because I don't feel like typing an entire program
     every time I want to run the program. */
int main() {
    FILE * GetInputFile(char f[]);
    FILE * GetOutputFile(char f[]);

    char f[40];  /* input and output file name */
    char line[MAXLINE];

    // FILE *input_file = GetInputFile("hope.txt");  /* input source code */
    // FILE *output_file = GetOutputFile("wish.txt"); /* modified source code */
    FILE *input_file = GetInputFile("CommentedProgram.c");  /* input source code */
    FILE *output_file = GetOutputFile("UncommentedProgram.c"); /* modified source code */

    FILE *temp_output_file = GetOutputFile("temp.txt");
    int c, len, i;
    int left_comment_characters;
    int right_comment_characters;
    
    /* Make sure there are a equal number of /* and */
    left_comment_characters = LeftCommentCharacters(line, input_file);
    rewind(input_file);
    right_comment_characters = RightCommentCharacters(line, input_file);
    if (left_comment_characters != right_comment_characters) {
        printf("Left and right comment character mismatch...pay attention.\n" );
        return 1;
    }
    rewind(input_file);

    
    /* remove comments */
    int prev_c, inside_comment = 0;
    /* Main loop */
    while ((c = fgetc(input_file)) != EOF) { 
        if (c == SLASH) {
            /* possible comment line */
            prev_c = c;
            c = fgetc(input_file);
            if (c == ASTERISK) {
                /* we have a comment */
                inside_comment = 1;
                while (((c = fgetc(input_file)) != EOF) && inside_comment) {
                    if (c == ASTERISK) {
                        /* possible end of comment */
                        c = fgetc(input_file);
                        if (c == SLASH) {
                            /* done with comment */
                            inside_comment = 0;
                        }
                    }
                }

            } else fputc(prev_c, temp_output_file);
        }       
        fputc(c, temp_output_file);
    }

    fclose(input_file);
    fclose(temp_output_file);
    FILE *temp_input_file = GetInputFile("temp.txt");

    /* remove blank lines */
    int index;
    while ((len = get_line_from_file(line, MAXLINE, temp_input_file)) > 0) {
        index = 0;
		while (WhiteSpace(line[index]) && index<len) {
            ++index;   
        }
        if (!WhiteSpace(line[index])) fprintf(output_file,"%s", line);

	}

    fclose(temp_input_file);
    fclose(output_file);
    remove("temp.txt");
    return 0;
}

int WhiteSpace(char c) {
    if (c == '\t' || c == '\n' || c == ' ' || c == '\b' || c == '\0') return 1;
    return 0;
}

int RightCommentCharacters(char s[], FILE * input_file) {
    int i, len;
    int n = 0;
    while ((len = get_line_from_file(s, MAXLINE, input_file)) > 0) {
        for (i = 0; i < len - 1; ++i) {
            if (s[i] == '*' && s[i+1] == '/' ) {
                ++n; } } }
    return n;
}

int LeftCommentCharacters(char s[], FILE * input_file) {
    int i, len;
    int n = 0;
    while ((len = get_line_from_file(s, MAXLINE, input_file)) > 0) {
        for (i = 0; i < len - 1; ++i) {
            if (s[i] == '/' && s[i+1] == '*' ) {
                ++n; } } }
    return n;
}

/* returns the length of the line...includes the \n but NOT the '\0'     */
int get_line_from_file(char s[], int lim, FILE * input_file) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = fgetc(input_file)) != EOF && c != '\n'; ++i) s[i] = c;
	if (c == '\n') { s[i] = c; ++i; }
	s[i] = '\0';
	return i;
}

FILE * GetInputFile(char f[]) {
    FILE *input_file;
    input_file = fopen(f, "r");
    if (!input_file) {
        printf("Could not open file for input\n"); 
    }
    return input_file;
}
FILE * GetOutputFile(char f[]) {
    FILE *output_file;
    output_file = fopen(f, "w");
    return output_file;
}