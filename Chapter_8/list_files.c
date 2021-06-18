#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


void listFiles(const char *path);

/* print file sizes */
int main(int argc, char **argv)
{
    if (argc == 1)       /* default:  current directory */
        //fsize(".");
        listFiles(".");
    else
        while (--argc > 0)
            //fsize(*++argv);
            listFiles(*++argv);


    return 0;
}



/**
 * Lists all files and sub-directories at given path.
 */
void listFiles(const char *path)
{
    struct dirent *dp;
    DIR *dir = opendir(path);
    if (!dir) return; 
    while ((dp = readdir(dir)) != NULL) printf("%s\n", dp->d_name);
    closedir(dir);
}