/* 
    Advanced Algorithms, Mar 2021
    Project 1 - String Matching
    Antonio Pimentel, 86385
*/

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd;
    char* t = NULL;
    char* p = NULL;
    size_t len_t = 0;
    size_t len_p = 0;
    ssize_t read_t;
    ssize_t read_p;

    while(1){
        cmd = getchar();
        getchar();
        switch (cmd){
            case 'T':
                read_t = getline(&t, &len_t, stdin);
                t[read_t-1] = '\0';
                printf("T string: %s\n", t);
                break;
            case 'N':
                read_p = getline(&p, &len_p, stdin);
                p[read_p-1] = '\0';
                printf("P string: %s\n", p);
                break;
            case 'K':
                read_p = getline(&p, &len_p, stdin);
                p[read_p-1] = '\0';
                printf("P string: %s\n", p);
                break;
            case 'B':
                read_p = getline(&p, &len_p, stdin);
                p[read_p-1] = '\0';
                printf("P string: %s\n", p);
                break;
            case 'X':
                free(t);
                free(p);
                printf("X\n");
                return EXIT_SUCCESS;
            default:
                printf("ERROR: Invalid command.\n");
                return EXIT_FAILURE;     
        }
    }
    return 0;
}
