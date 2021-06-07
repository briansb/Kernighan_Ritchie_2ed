#include <stdio.h>
#include <string.h>


/* command:    ./a.out hello brian stephen */
int main(int argc, char *argv[])
{
    /* need to understand:

        (*++argv)[0]  
                    */

    
    for (int i = 0; i < argc; ++i) {
        printf("argv = %s\n", argv[i]);
    }
    printf("\n");
    
    for (int i = 0; i < argc; ++i) {
        printf("%s at address %p\n", *(argv + i), argv + i);
    }
    printf("\n");

    // printf("++*argv = %s\n", ++*argv);  /*   /a.out   */
    // printf("++*argv = %s\n", ++*argv);  /*   a.out    */
    // printf("++*argv = %s\n", ++*argv);  /*   .out     */

    // printf("*++argv = %s\n", *++argv);      /*  hello  */
    // printf("*++argv = %s\n", *++argv);      /*  brian  */
    // printf("*++argv = %s\n", *++argv);      /*  stephen  */

    // printf("*++argv[0] = %c\n", *++argv[0]);    /*  /  */
    // printf("*++argv[0] = %c\n", *++argv[0]);    /*  .  */
    // printf("*++argv[0] = %c\n", *++argv[0]);    /*  a  */

    // printf("*++argv[0] = %c\n", *++argv[1]);    /*  e  */
    // printf("*++argv[0] = %c\n", *++argv[1]);    /*  l  */
    // printf("*++argv[0] = %c\n", *++argv[1]);    /*  l  */

    printf("(*++argv)[0] = %c\n", (*++argv)[0]);    /*  h  */
    printf("(*++argv)[0] = %c\n", (*++argv)[0]);    /*  b  */
    printf("(*++argv)[0] = %c\n", (*++argv)[0]);    /*  s  */

    return 0;
}
