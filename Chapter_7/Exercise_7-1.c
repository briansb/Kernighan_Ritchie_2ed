#include <stdio.h>
#include <ctype.h>  /* tolower, toupper */
#include <string.h>  /* strcmp */

int main(int argc, char *argv[])   /* lower:  convert input to lower case */
{
    int c;

    //++*argv; ++*argv;  /* moves past initial ./  */
    printf("Program invoked with %s\n", argv[0]);

    if (strcmp(argv[0], "./lower") == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    } else if (strcmp(argv[0], "./upper") == 0) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    } else {
        while ((c = getchar()) != EOF)
            putchar(c);
    }
    
    return 0;

}