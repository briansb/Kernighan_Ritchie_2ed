#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

#define BUFSIZE 1024

void filecopy(int f1, int f2);
void error(char*, ...);

char buf[BUFSIZE];

/* cat:  concatenate files, version 3 */
int main(int argc, char *argv[]) {
    int f1;
    
    char *prog = argv[0];      /* program name for errors */
    
    if (argc == 1)  /* no args: copy standard input */
        filecopy( 0, 1); /* 0 = stdin, 1 = stdout */
    else
        while (--argc > 0) {
            if ((f1 = open(*++argv, O_RDONLY, 0)) == -1)
                error("cat:  can't open %s", *argv);
            else
                filecopy(f1, 1);  
            fprintf( stdout, "\n");
            close(f1);   
        }
    exit(0);

}
/* filecopy:  copy file ifp to file ofp */
void filecopy(int f1, int f2) {
    int n;
    while ((n = read(f1, buf, BUFSIZE)) > 0)
        write(f2, buf, n);

    return;
}
/* error:  print an error message and die */
void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error:  ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}