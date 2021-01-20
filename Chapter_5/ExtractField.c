#include <stdio.h>

#define MAXLEN 1000     /* max length of any input line */

void ExtractField(char *str1, int field_number, char *str2);
int getline_bb(char *, int);

/* extract a field from a string 
   assumes space delimiters */
int main () {

    int len;
    char line[MAXLEN];
    char field[MAXLEN];

    while ((len = getline_bb(line, MAXLEN)) > 0) {
        ExtractField(line, 3, field);
        printf("Extraction ->%s<-\n", field);
    }
    return 0;
}

/* get_line:  read a line into s, return length */
/* does NOT return \n */
int getline_bb(char s[], int lim)
{
    int c, i;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i] = '\0';
    return i;
}

void ExtractField(char *str1, int field_number, char *str2) {
    /* assumes space is field delimiter */
    int i = 0;
    int j = 0;
    while (str1[i] == ' ') {   /* ignore leading spaces */
        i++;
    }
    while ( --field_number) {
        while (str1[i++] != ' ' && str1[i] != '\0') {
            ;
        }
    }

    if (str1[i] == '\0') { str2[0] = '\0'; return; }

    while (str1[i] != ' ' && str1[i] != '\0') {
        str2[j++] = str1[i++];
    }
    str2[j] = '\0';
    return;
}

