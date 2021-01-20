#include <stdio.h>
#include <string.h>

#define MAXCHARS 1000
#define NOTHING -1

void expand(char s1[], char s2[]);
void fill(char a, char b, char s[]);
int is_letterornumber(char c);
void string_copy(char s1[], char s2[]);
void string_concatenation(char s[], char t[]);

int main() {
    char s1[MAXCHARS], s2[MAXCHARS];
    
    int i = 0;
    char c;
    while ((c = getchar()) != '\n') {
        s1[i++] = c;
    }
    s1[i] = '\0';

    expand(s1, s2);

    i = 0;
    while ((c = s2[i++]) != '\0') printf("%c", c);
    printf("\n");


    return 0;
}

void expand(char s1[], char s2[]) {
    
    int i;
    char firstitem = NOTHING;
    char lastitem = NOTHING;
    char temp[MAXCHARS];
    int have_hyphen = 0;
    s2[0] = '\0';

    for (i = 0; i < strlen(s1); ++i) {
        if (is_letterornumber(s1[i])) {
            if (firstitem == NOTHING && !(have_hyphen)) {
                firstitem = s1[i];
            } else if (firstitem != NOTHING && (have_hyphen)){
                lastitem = s1[i];
                fill(firstitem, lastitem, temp);
                string_concatenation(s2, temp);
                firstitem = NOTHING;
                have_hyphen = 0;
            } 
            else if (firstitem == NOTHING && (have_hyphen)){
                firstitem = lastitem;
                lastitem = s1[i];
                fill(firstitem, lastitem, temp);
                string_concatenation(s2, temp);
                firstitem = NOTHING;
            }
            //printf("number or letter\n");
        } else if (s1[i] == '-') {
            /* check for leading hyphen */
            if (firstitem == NOTHING && lastitem == NOTHING) {
                temp[0] = '-';
                temp[1] = '\0';
                string_concatenation(s2, temp);
            }
            /* check for trailing hyphen */
            else if (i == strlen(s1)-1) {
                temp[0] = '-';
                temp[1] = '\0';
                string_concatenation(s2, temp);
            } else if (firstitem != NOTHING || lastitem != NOTHING) {
                have_hyphen = 1;
            }
            //printf("hyphen\n");
        } else {
            printf("Illegal character. No operation performed.\n");
            string_copy(s1, s2);
        }
    }

    return;
}
/* fills array from a to b...lowercase, uppercase, or numeric */
/* assumes a<=b */
void fill(char a, char b, char s[]) {
    int index;
    for (index = 0; index <= b-a; ++index) {
        s[index] = a + index;
    }
    s[index] = '\0';

}
int is_letterornumber(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) return 1;
    return 0;
}
void string_copy(char s1[], char s2[]) {
    int i = 0;
    int j = 0;
    while (s1[i] != '\0') s2[j++] = s1[i++];
    s2[j] = '\0';
    return;
}
/* concatenate t to end of s; s must be big enough */
void string_concatenation(char s[], char t[]) {
    int i, j;

    i = j = 0;
    /* find end of s */
    while (s[i] != '\0') i++;

    /* copy t to end of s */
    while ((s[i++] = t[j++]) != '\0') 
        ;
}