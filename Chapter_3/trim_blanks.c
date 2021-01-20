#include <stdio.h>
#include <string.h>

/* trim:  remove leading blanks, tabs, newlines */
int trim_leading(char s[]);
/* trim:  remove trailing blanks, tabs, newlines */
int trim_trailing(char s[]);

int main() {
    char s[] = "          this        ";
    trim_leading(s);
    trim_trailing(s);

    printf("The new string =%s.\n",s);

    return 0;
}
/* trim:  remove trailing blanks, tabs, newlines */
int trim_trailing(char s[]) {
    int n;
    /* starts at beginning and scans for white space.
       when non-whitespace found, remaining string shifted */
    for (n = strlen(s)-1; n>=0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}

/* trim:  remove leading blanks, tabs, newlines */
int trim_leading(char s[]) {
    int n;
    /* starts at beginning and scans for white space.
       when non-whitespace found, remaining string shifted */
    for (n = 0; n < strlen(s); n++)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    int i = 0;
    while (s[n] != '\0') {
        s[i++] = s[n++];
    }
    s[i] = '\0';
    return n;
}