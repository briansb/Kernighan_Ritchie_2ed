#include <stdio.h>

#define MAXLINE 10
int main() {
    /* write the following without using && or || */
    /*      for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)     */
    /*              s[i] = c;                                                */
    
    /*   evaluation of above is done from left to right, and stops as soon as truth is known  */
    /*   parentheses are needed for c=getchar() since != has a higher precedence than =
             we want the assignment to occur first   */

   int lim = MAXLINE; /* longest line */
   int i = 0;
   char s[MAXLINE];
   char c;

   while (i < lim -1) {
       c = getchar();
       if (c == '\n') {
           i = lim;
       } else if ( c == EOF) {
           i = lim;
       } else s[i] = c;
       ++i;
   }

    printf("Input array = %s\n", s);



   return 0;
}