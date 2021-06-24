#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024

void file_size(char *);
void dirwalk(char *, void(*fcn)(char *));

/* print file sizes...has directory walk */
int main(int argc, char **argv)
{
    if (argc == 1)       /* default:  current directory */
        file_size(".");
    else
        while (--argc > 0)
            file_size(*++argv);

    return 0;
}

/* dirwalk:  apply fcn to all files in dir */
void dirwalk(char *dir, void(*fcn)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk:  can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;               /* skip self and parent */
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk:  name %s/%s to long\n", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
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
        dirwalk(name, file_size);
        //printf("%s is a directory\n", name);
    }
    else if ((stbuf.st_mode & S_IFMT) == S_IFREG)
        printf("%s \t %8ld bytes\n", name, stbuf.st_size);
    else
        printf("%s is something else\n", name);
    
}


