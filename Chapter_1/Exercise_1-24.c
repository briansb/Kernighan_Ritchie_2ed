#include <stdio.h>

#define SPACE 32
#define RETURN 10
#define SLASH 47
#define BACKSLASH 92
#define ASTERISK 42
#define EOL '\n'
#define LEFTPARENTHESIS 40
#define RIGHTPARENTHESIS 41
#define LEFTBRACKET 91
#define RIGHTBRACKET 93
#define LEFTBRACE 123
#define RIGHTBRACE 125
#define SINGLEQUOTE 39
#define DOUBLEQUOTE 34

typedef enum {false, true} bool;
char leading_comment_char[] = "/*'";
char ending_comment_char[] = "*/";

FILE * GetInputFile(char f[]);

/* syntax checker */
int main() {
    
    int c, c_previous;
    FILE *input_file = GetInputFile("TestProgram.c");  /* input source code */

    int ParenthesisToggle = 0;
    int BracketToggle = 0;
    int BraceToggle = 0;
    int SingleQuoteToggle = 0;
    int DoubleQuoteToggle = 0;
    int EscapeCharacterPlacement = 0;
    int UnknownEscapeCharacter = 0;
    int CommentToggle = 0;

    /* 1. read every character */
    /* 2. check for syntax character...see #define above */
    /* 3. keep running total */
    /* NOTE:  when inside a comment, do no syntax checking */
    while ((c = fgetc(input_file)) != EOF) { 
        if (CommentToggle == 1) {
            /* ignore syntax in comments */
        }
        else if ( c == LEFTPARENTHESIS ) {
            ++ParenthesisToggle;
        }
        else if ( c == RIGHTPARENTHESIS ) {
            --ParenthesisToggle;
        } 
        else if ( c == LEFTBRACKET) {
            ++BracketToggle;   
        }
        else if ( c == RIGHTBRACKET) {
            --BracketToggle;
        }
        else if ( c == LEFTBRACE ) {
            ++BraceToggle;
        }
        else if ( c == RIGHTBRACE ) {
            --BraceToggle;
        }
        else if ( c == SINGLEQUOTE ) {
            if (SingleQuoteToggle == 0 ) SingleQuoteToggle = 1;
            else SingleQuoteToggle = 0;
        }
        else if ( c == DOUBLEQUOTE ) {
            if (DoubleQuoteToggle == 0 ) DoubleQuoteToggle = 1;
            else DoubleQuoteToggle = 0;
        }
        else if ( c == BACKSLASH ) {
            /* escape characters always occur between single or double quotes */
            if ( DoubleQuoteToggle != 1 && SingleQuoteToggle != 1) EscapeCharacterPlacement = 1;
        }
        else if ( c_previous == BACKSLASH ) {
            if ( c != '0' && c != 'a' && c != 'b' && c != 'e' && c != 'f' && c != 'n' && c != 'r' && c != 't' 
                          && c != 'v' && c!= BACKSLASH && c != SINGLEQUOTE && c != DOUBLEQUOTE && c != '?' ) UnknownEscapeCharacter = 1;
        }
        if ( c == SLASH && c_previous == ASTERISK) {
            --CommentToggle;
        }
        else if ( c == ASTERISK && c_previous == SLASH) {
            ++CommentToggle;
        }
        
        c_previous = c;
    }


    /* results */
    if ( ParenthesisToggle != 0 ) printf("Unbalanced parentheses\n");
    if ( BracketToggle != 0 ) printf("Unbalanced brackets\nparentheses");
    if ( BraceToggle != 0 ) printf("Unbalanced braces\n");
    if ( SingleQuoteToggle != 0 ) printf("Unbalanced single quotes\n");
    if ( DoubleQuoteToggle != 0 ) printf("Unbalanced double quotes\n");
    if ( EscapeCharacterPlacement == 1 ) printf("Escape sequence outside quotes\n");
    if ( UnknownEscapeCharacter == 1 ) printf("Unknown escape character\n");
    if ( CommentToggle != 0 ) printf("Unbalanced comment characters\n");

    if ( ParenthesisToggle == 0 && BracketToggle == 0 && BraceToggle == 0 && SingleQuoteToggle == 0 && DoubleQuoteToggle == 0 
                                && EscapeCharacterPlacement == 0 && UnknownEscapeCharacter == 0 && CommentToggle == 0) 
        printf("No syntax errors.\n");
        
    fclose(input_file);
    return 0;
}

FILE * GetInputFile(char f[]) {
    FILE *input_file;
    input_file = fopen(f, "r");
    if (!input_file) {
        printf("Could not open file for input\n"); 
    }
    return input_file;
}