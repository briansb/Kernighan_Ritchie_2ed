#include <stdio.h>

#define MAXCHARS 1000
#define BACKSLASH 92 /* ASCII value of \ */
#define NEWLINE 10
#define TAB 9
#define BACKSPACE 8
void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main() {
    char s[MAXCHARS], t[MAXCHARS], u[MAXCHARS];
    
    int i = 0;
    char c;
    while ((c = getchar()) != EOF) {
        s[i++] = c;
    }
    s[i] = '\0';

    escape(s,t);

    i = 0;
    while ((c = t[i++]) != '\0') printf("%c", c);
    printf("\n");

    unescape(t,u);

    i = 0;
    while ((c = u[i++]) != '\0') printf("%c", c);
    printf("\n");

    return 0;
}
/* turns /char into the escape character */
void unescape(char s[], char t[]) {
    int i = 0;
    int j = 0;
    while (s[i] != '\0') {
        if (s[i] == BACKSLASH) {
            switch (s[++i]) {
                case 'n':
                    t[j++] = NEWLINE;
                    break;
                case 't':
                    t[j++] = TAB;
                    break;
                case 'b':
                    t[j++] = BACKSPACE;
                    break;
                default:
                    t[j++] = BACKSLASH;
                    t[j++] = s[i];
            }
        } else { t[j++] = s[i]; }
        i++;
    }
    t[j] = '\0';
    return;
}

/* turns escape characters into \char */
void escape(char s[], char t[]) {
    int i = 0;
    int j = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case '\n':
                t[j++] = BACKSLASH;
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = BACKSLASH;
                t[j++] = 't';
                break;
            case '\b':
                t[j++] = BACKSLASH;
                t[j++] = 'b';
                break;
            default:
                t[j++] = s[i]; 
        }
        i++;
    }
    t[j] = '\0';
    return;
}