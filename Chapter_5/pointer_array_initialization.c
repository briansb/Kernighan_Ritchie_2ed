#include <stdio.h>

char *name[13];    /* array of pointers to month names */
char *month_name(int n);

int main() {
    int n = 3;
    char *ptr;
    ptr = month_name(n);
    printf("%s\n", ptr);
    return 0;

}
/* month_name:  return name of nth month */
char *month_name(int n) {
    static char *name[] = {
        "Illegal month",
        "January", "February", "March", "April", 
        "May", "June", "July", "August", 
        "September", "October", "November", "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}