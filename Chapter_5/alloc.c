#include <stdio.h>

#define ALLOCSIZE 10000  /* size of available space */

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

char *alloc(int n)      /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        /* there is enough room for request */
        allocp += n;
        return allocp - n;  /* return pointer must point to BEGINNING of requested storage */
    } else {
        return 0;  /* not enough room */
    }
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        /* only checks for p within allocbuf boundaries */
        allocp = p;
}

int main() {
    char *char_ptr;
    printf("allocbuf starts at \t\t%p\n", allocbuf);
    char_ptr = alloc(100);
    printf("After request for 100 characters...\n");
    printf("p has value \t\t\t%p\n", char_ptr);
    printf(" and the next free position is \t%p\n", allocp);

    char_ptr = alloc(2);
    printf("After request for 2 characters...\n");
    printf("p has value \t\t\t%p\n", char_ptr);
    printf(" and the next free position is \t%p\n", allocp);
    return 0;
}