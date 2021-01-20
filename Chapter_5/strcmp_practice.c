#include <stdio.h>
#include <string.h> /* for strcmp */
#include <ctype.h>  /* for tolower */

int getline_bb(char s[], int lim);

/* sort input lines */
int main (int argc, char *argv[]) {

    char str1[10];
    getline_bb(str1, 100);

    char str1temp[10];
    int i = 0;
    while (str1temp[i++] =  tolower(str1[i]));


    printf("String = %s, Copy = %s\n", str1, str1temp);




    // if (strcmp(str1, str2) < 0) printf("%s comes before %s\n", str1, str2);
    // if (strcmp(str1, str2) > 0) printf("%s comes before %s\n", str2, str1);
    // if (strcmp(str1, str2) == 0) printf("%s equals %s\n", str1, str2);
    


}
/* string_compare:  wrapper for strcmp */
// int string_compare(char *str1, char *str2) {
//     if (fold) {
//         /* convert str1 and str1 to lowercase */
//     }
//     /* reverse arguments if -r */
//     if (reverse) return strcmp(str2, str1);
//     else return strcmp(str1, str2);
// }

/* get_line:  read a line into s, return length */
int getline_bb(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    s[i] = '\0';
    return i;
}
