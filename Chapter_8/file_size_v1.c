#include <stdio.h>
#include <sys/stat.h>

void file_size(char *);

/* print file size...no directory walk */
int main(int argc, char **argv)
{
    if (argc == 1)       /* default:  current directory */
        file_size(".");
    else
        while (--argc > 0)
            file_size(*++argv);

    return 0;
}

/* prints file sizes */
void file_size(char *name)
{   
    struct stat stbuf;  /* structure defined in sys/stat.h
                           illustrated on page 180  */

    if (stat(name, &stbuf) == -1) {    /* stat is a system call that returns the inode information, pg 180 */
        fprintf(stderr, "fsize:  can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        printf("%s is a directory\n", name);
    }
    else if ((stbuf.st_mode & S_IFMT) == S_IFREG)
        printf("%s - size = %8ld bytes\n", name, stbuf.st_size);
    else
        printf("%s is something else\n", name);
    
}
