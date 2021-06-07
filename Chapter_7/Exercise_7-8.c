#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINELENGTH 1000
#define LINESPERPAGE 20

int fgetline(char *line, int max, FILE *fin);
char *fgets(char *s, int n, FILE *iop);

/*find:  print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    int found;
    char pattern[MAXLINELENGTH];
    int line_count;
    int page_count;
    
    if (argc < 2)
        printf("Usage: file1 file2 ...\n");
    else {
        *argv++; /* increment argv to first filename */
        while (argc-- > 1) {
            printf("\f\n");
            printf("\t\tPrinting %s\n", *argv);
            FILE *fp;
            if (( fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "Can not open %s\n", *argv);
                exit(1);
            }
            line_count = 1;
            page_count = 1;
            while (  (found = fgetline(line, MAXLINELENGTH, fp)) != 0  ) {
                    printf("%s", line);
                    line_count++;
                    if (line_count > LINESPERPAGE) {
                        printf("Page %d\n", page_count);
                        printf("\f\n");
                        line_count = 1;
                        page_count++;
                    }
            }
            printf("\nPage %d\n", page_count);
            fclose(fp);
            *argv++;
        }
    }
    printf("\n");
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
