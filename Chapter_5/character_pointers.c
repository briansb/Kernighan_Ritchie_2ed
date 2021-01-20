#include <stdio.h>
#include <string.h>

int main() {

    char *ptr = "birmingham";
    printf("%s\n", ptr);
    printf("%s\n", ptr+3);
    printf("%c is offset 3.\n", *(ptr+3));

    char *ptr1;
    ptr1 = "brian";
    printf("%s\n", ptr1);
    

    return 0;
}
