/*
Implementare un programma parallelo per l'ambiente multicore con npxnp unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1)Il core master deve generare una matrice A di dimensione NxN
2)Ogni core deve sommare tra loro gli elementi di un blocco quadrato della matrice A di dimensione (N/np)x(N/np), conservando i valori in un vettore b
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
int main() {
    int N, nthreads,np, i, j;
    double **A, *b;
    int blocksize;

    printf("Inserire il size della Matrice:\n");
    scanf("%d", &N);

    printf("Inserire il numero di threads:\n");
    scanf("%d", &np);

    nthreads=np*np;
    

    A = (double **)calloc(N, sizeof(double *));
    for (i = 0; i < N; i++) 
    {
        A[i] = (double *)calloc(N, sizeof(double));
    }

    int num_blocks = (N*N)/nthreads;
    b = (double *)calloc(num_blocks, sizeof(double));

    srand(time(NULL));
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            A[i][j] = rand() % 10 + 1;
        }
    }

    printf("La matrice A ha i seguenti valori:\n");
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            printf("A[%d][%d]=%lf ", i, j, A[i][j]);
        }
        printf("\n");
    }

    blocksize = N / np;
//decomposizione blocchi riga colonna
    #pragma omp parallel for num_threads(nthreads) private(i, j)
    for (int block_id = 0; block_id < num_blocks; block_id++) 
    {
        int blockrow = (block_id / (N / blocksize)) * blocksize;//riga
        int blockcol = (block_id % (N / blocksize)) * blocksize;//colonna (modulo)


        for (i = blockrow; i < blockrow + blocksize && i < N; i++) 
        {
            for (j = blockcol; j < blockcol + blocksize && j < N; j++) 
            {
                b[block_id] += A[i][j];
            }
        }


    }
    printf("Il vettore B ha i seguenti valori:\n");
    for (i = 0; i < num_blocks; i++) 
    {
        printf("b[%d]=%lf\n", i, b[i]);
    }

    for (i = 0; i < N; i++) 
    {
        free(A[i]);
    }
    free(A);
    free(b);

    return 0;
}
