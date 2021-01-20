#include <stdio.h>

#define MAXLINE 20

int htoi(char s[], int len);
int get_line(char s[], int lim);

/* converts a hex integer to decimal */
int main() {
    int len, retval;
    char line[MAXLINE];
    printf("Enter hexadecimal number to be converted to decimal...");
    while ((len = get_line(line, MAXLINE)) > 0) {
            retval = htoi(line, len);
            if (retval == -1) printf("Illegal hexadecimal digit\nEnter hexadecimal number to be converted to decimal...");
            else printf("%s = %d\nEnter hexadecimal number to be converted to decimal...", line, retval);
	}
	return 0;
}

/* converts char array of hex digits to integer */
int htoi(char s[], int len) {
    int index = 0;
    int integer_number = 0;
    /* check for 0x or 0X at beginning */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        index = 2;
    }

    for (index; index < len; ++index) {
    /* must check three ranges - '0' to '9', 'a' to 'f', 'A' to 'F' */
        if (s[index] >= '0' && s[index] <= '9') {
            integer_number = 16 * integer_number + (s[index] - '0');
        }
        else if (s[index] >= 'A' && s[index] <= 'F') {
            integer_number = 16 * integer_number + ((s[index] - 'A') + 10);
        }
        else if (s[index] >= 'a' && s[index] <= 'f') {
            integer_number = 16 * integer_number + ((s[index] - 'a') + 10);
        }
        else {
            return -1;
        }
    }

    return  integer_number;
}

int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) s[i] = c;
    s[i] = '\0';
    return i;
}