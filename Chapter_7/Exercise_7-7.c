#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINELENGTH 1000

int fgetline(char *line, int max, FILE *fin);
char *fgets(char *s, int n, FILE *iop);
void strcpy_pointer_final(char *s, char *t);

/*find:  print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    int found;
    char pattern[MAXLINELENGTH];
    
    if (argc < 2)
        printf("Usage: pattern file1 file2 ...\n");
    else if (argc == 2) {   /* no files, use stdin */
        printf("Using stdin\n");
        strcpy_pointer_final(pattern, argv[1]);
        while ( (found = fgetline(line, MAXLINELENGTH, stdin)) > 0) {
            if ( (strstr(line, argv[1])) != NULL ) {
                printf("Found %s in stdin\n", pattern);
            }
        }
    } else {
        strcpy_pointer_final(pattern, argv[1]);
        *argv++;
        *argv++; /* increment argv to first filename */
        while (argc-- > 2) {
            printf("Searching for %s in %s\n", pattern, *argv);
            FILE *fp;
            if (( fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "Can not open %s\n", *argv);
                exit(1);
            }
            while (  (found = fgetline(line, MAXLINELENGTH, fp)) != 0  ) {
                if ( strstr(line, pattern) != NULL ) {
                    printf("Found %s in %s\n", pattern, *argv);
                }
            }
            fclose(fp);
            *argv++;
        }
    }

    return 0;
}
/* fgetline:  read a line from fin, return length */
int fgetline(char *line, int max, FILE *fin) {
    if (fgets(line, max, fin) == NULL)
        return 0;
    else
        return strlen(line);
}
/* fgets:  get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}
/* strcpy:  copy t to s; pointer version 3 */
void strcpy_pointer_final(char *s, char *t) {
    while (*s++ = *t++) /* we only need to check for zero */
        ;
}