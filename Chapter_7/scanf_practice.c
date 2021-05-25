#include <stdio.h>
#include <string.h>

char line[100];

void readline();
int getline_bb(char s[], int lim);

int main() {
    
    readline();

    // readline();

    // readline();

    return 0;
}

void readline() {

    int j = 0;
    char *ptr;
    char s[10];

    ptr = line;

    getline_bb(ptr, 100);

    for (ptr = line; *ptr; ptr += strlen(s)+1) {
        j = sscanf(ptr, "%s", s); /* adds \0 to end 
                                     if last item, strips \n and adds \0 */
        printf("Found %s with count %d\n", s, j);
    }

    printf("Exhausted line\n");  /* return \n here */

}

int getline_bb(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}