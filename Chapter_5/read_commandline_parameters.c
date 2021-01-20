#include <stdio.h>
#include <string.h>

int a_flag = 0;
int b_flag = 0;
int c_flag = 0;
int d_flag = 0;
int e_flag = 0;

int read_command_line(int argc, char *argv[]);

/* routine to read command line parameters...
   ./progname -a -b -cd -e 
   global variables default to false, set to 1 upon detection */
int main (int argc, char *argv[]) {
    
    if ( read_command_line(argc, argv)) {
        printf("Incorrect command line arguments\n");
        return 1;
    } else {
        printf("a_flag = %d\n", a_flag);
        printf("b_flag = %d\n", b_flag);
        printf("c_flag = %d\n", c_flag);
        printf("d_flag = %d\n", d_flag);
        printf("e_flag = %d\n", e_flag);
    }

    return 0;
}
int read_command_line(int argc, char *argv[]) {
    int arg_length = 0;
    char arg_value;
    while (--argc) {
        printf("arg = %s\n", *++argv);
        if ( *argv[0] != '-') return 1;
        arg_length = strlen(*argv);
        printf("\targ length = %d\n",arg_length);
        while (--arg_length) {
            //arg_value = *(   (*argv) + 1     );
            arg_value = *(   ++(*argv)     );
            printf("\t\targ value = %c\n", arg_value);

            switch(arg_value) {
                case 'a':
                    a_flag = 1;
                    break;
                case 'b':
                    b_flag = 1;
                    break;
                case 'c':
                    c_flag = 1;
                    break;
                case 'd':
                    d_flag = 1;
                    break;
                case 'e':
                    e_flag = 1;
                    break;
            }
        }
    }

    return 0;
}
