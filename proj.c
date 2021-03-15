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
ssize_t n = 0; /* num characters in text t */
ssize_t m = 0; /* num characters in pattern p */

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
    int i, k;
    int* prefixTable = malloc(m*sizeof(int));
    prefixTable[0] = 0;
    for (i=0; i<m-1; i++)
        if (p[i+1] == p[prefixTable[i]])
            prefixTable[i+1] = prefixTable[i]+1;
        else
            prefixTable[i+1] = 0;
    k=0;
    for (i=0; i<n; i++)
        if (p[k] == t[i])
            if (k==m-1){
                printf("%d ", i-k);
                k = prefixTable[k];
            }
            else
                k++;
        else if (k>0){
            k = prefixTable[k-1];
            i--;
        }
    printf("\n");
    free(prefixTable);
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
