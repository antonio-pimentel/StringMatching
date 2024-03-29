/* 
    Advanced Algorithms, April 2021
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
        for (j=0; t[i+j] == p[j] && j<m; j++);
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
    printf("\n%d \n", count);
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

int* createNTable() {
    int i, l, r;
    int* N = malloc(sizeof(int)*m);
    int* Z = malloc(sizeof(int)*m);
    char* reverse = malloc(sizeof(char)*m);
    /* Reverse p */
    for (i=0; i<m; i++)
        reverse[i] = p[m-i-1];
    /* Z algorithm */
    l = r = 0;
    for (i = 1; i < m; i++) 
        if (i >= r) {
            l = r = i;
            while (r < m && reverse[r-l] == reverse[r]) r++;
            Z[i] = r-l;
        }
        else
            if (Z[i-l] < r-i)
                Z[i] = Z[i-l];
            else {
                l = i;
                while (r < m && reverse[r-l] == reverse[r]) r++;
                Z[i] = r-l;
            }
    /* Reverse Z to get N(P) */
    for (i=0; i<m; i++)
        N[i] = Z[m-i-1];
    free(Z);
    free(reverse);
    return N;
}

void BoyerMoore(){
    int i,j, count;
    int* L = malloc(m*sizeof(int));
    int* l = malloc(m*sizeof(int));
    /* Bad Character */
    int* badCharTable = malloc(4*sizeof(int));/*A,C,G,T*/
    for (i=0; i<4; i++)
        badCharTable[i] = -1;
    for (i=0; i<m; i++)
        badCharTable[alphabetToIndex(p[i])] = i;
    #define BADCHAR_INC MAX(j-badCharTable[alphabetToIndex(t[i+j])],1)
    /* Strong Good Suffix */
    int* N = createNTable(p,m);
    for (i=0; i<m; i++)
        L[i] = l[i] = 0;
    int largest_j = 0;
    for (j=0; j<m-1; j++){
        if(m-N[j] < m)
            L[m-N[j]] = j+1;
        if (N[j] == j+1)
            largest_j = j+1;
        l[m-1-j] = largest_j;
    }
    #define GOODSUFFIX_INC j == m-1 ? 1                         \
                                    : L[j+1] > 0 ? m - L[j+1]   \
                                                 : m - l[j+1]
    /* Search */
    count = i = 0;
    while(i <= n-m){
        for (j = m-1; j>=0 && ++count && t[i+j] == p[j]; j--);
        if (j<0){ /*match found*/
            printf("%d ", i);
            i += m - l[1];
        }
        else i += MAX(BADCHAR_INC, GOODSUFFIX_INC);
    }
    printf("\n%d \n", count);
    free(badCharTable);
    free(N);
    free(L);
    free(l);
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
