/* 
    Advanced Algorithms, Mar 2021
    Project 1 - String Matching
    Antonio Pimentel, 86385
*/

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

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
    int i, k, count;
    int* prefixTable = malloc(m*sizeof(int));
    prefixTable[0] = 0;
    for (i=0; i<m-1; i++)
        if (p[i+1] == p[prefixTable[i]])
            prefixTable[i+1] = prefixTable[i]+1;
        else
            prefixTable[i+1] = 0;
    k=0;
    count=0;
    for (i=0; i<n; i++) {
        while(k>0 && p[k] != t[i]){
            k = prefixTable[k-1];
            count++;
        }
        count++;
        if (p[k] == t[i])
            k++;
        if (k == m) {
            printf("%d ",i-k+1);
            if (i<n-1){
                k= prefixTable[k-1];
                count++;
            }
        }
    }
    /*
    k=0;
    count=0;
    for (i=0; i<n; i++){
        count++;
        if (p[k] == t[i])
            if (k==m-1){
                printf("%d ", i-k);
                if (i<n-1){
                    k = prefixTable[k];
                    count++;
                }
            }
            else
                k++;
        else if (k>0){
            k = prefixTable[k-1];
            count++;
            i--;
        }
    }
    */
    printf("\n%d\n", count);
    free(prefixTable);
}

int alphabetToIndex(char c){
    switch (c){
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default:
            printf("ERROR: The current Boyer-Moore implementation \
            only supports patterns with the alphabet: A, C, G, T.\n");
            return -1;
    }
}

void BoyerMoore(){
    int i,j;
    int* badCharTable = malloc(4*sizeof(int));/*A,C,G,T*/
    for (i=0; i<4; i++)
        badCharTable[i] = -1;
    for (i=0; i<m; i++)
        badCharTable[alphabetToIndex(p[i])] = i;
    i = 0;
    while(i <= n-m){
        for (j = m-1; t[i+j] == p[j] && j>=0; j--){}
        if (j==-1) /*match found*/
            printf("%d ", i++);
        else /*char doesn't match*/
            i += MAX(j-badCharTable[alphabetToIndex(t[i+j])], 1);
    }
    printf("\n");
    free(badCharTable);
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
                BoyerMoore();
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
