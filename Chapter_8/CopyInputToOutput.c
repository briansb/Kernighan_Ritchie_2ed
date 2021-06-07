#include <unistd.h>

#define BUFSIZE 1024

/* see:
    https://pubs.opengroup.org/onlinepubs/000095399/functions/read.html
    https://pubs.opengroup.org/onlinepubs/000095399/functions/write.html
*/

/* can use redirection for non-console files */

int main()   /* copy input to output */
{
    char buf[BUFSIZE];
    int n;
    while ((n = read(0, buf, BUFSIZE)) > 0)
        write(1, buf, n);
    
    return 0;
}