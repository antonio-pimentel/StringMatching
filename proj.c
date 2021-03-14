/* 
    Advanced Algorithms, Mar 2021
    Project 1 - String Matching
    Antonio Pimentel, 86385
*/

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

char* t = NULL;
char* p = NULL;
ssize_t n; /* num characters in text t */
ssize_t m; /* num characters in pattern p */

void NaivePatternSearch(){
    int i, j;
    for (i=0; i<=n-m; i++){
        for (j=0; t[i+j] == p[j] && j<m; j++){}
        if (j==m)
            printf("%d ",i);
    }
    printf("\n");
}

void KnuthMorrisPratt(){

    


    printf("\n");
}

int main() {
    char cmd;
    size_t len_t = 0; /* lenght of memory allocated for t */
    size_t len_p = 0;
    while(1){
        cmd = getchar();
        getchar();
        switch (cmd){
            case 'T': /* Get Text Sequence */
                n = getline(&t, &len_t, stdin);
                t[--n] = '\0';
                break;
            case 'N': /* Naive Search */
                m = getline(&p, &len_p, stdin);
                p[--m] = '\0';
                NaivePatternSearch();
                break;
            case 'K': /* Knuth-Morris-Pratt */
                m = getline(&p, &len_p, stdin);
                p[--m] = '\0';
                KnuthMorrisPratt();
                break;
            case 'B': /* Boyer-Moore */
                m = getline(&p, &len_p, stdin);
                p[--m] = '\0';
                break;
            case 'X': /* Exit */
                free(t);
                free(p);
                return EXIT_SUCCESS;
            default:
                printf("ERROR: Invalid command.\n");
                return EXIT_FAILURE;     
        }
    }
    return EXIT_FAILURE;
}
