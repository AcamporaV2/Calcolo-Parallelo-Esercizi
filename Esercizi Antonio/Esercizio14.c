/*
Implementare un programma parallelo per l'ambiente multicore con npxnp unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve leggere una matrice A di dimensione MxM.
2)Ogni core deve estrarre un blocco della matrice A di dimensione (M/np)x(M/np)
conservando i valori in npxnp matrici.
3)Infine, i core devono collaborare per calcolare la somma di tali matrici
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int i, j, M, q, p;
    double **A;

    // Lettura delle dimensioni della matrice e del numero di core per riga e colonna
    printf("Inserire la dimensione della matrice (MxM): \n");
    scanf("%d", &M);

    printf("Inserire il numero di core per riga (q): \n");
    scanf("%d", &q);

    printf("Inserire il numero di core per colonna (p): \n");
    scanf("%d", &p);

    int blockSize = M / q;
    int nthreads = q * p;

    // Allocazione della matrice A
    A = (double **)malloc(M * sizeof(double *));
    for (i = 0; i < M; i++) {
        A[i] = (double *)malloc(M * sizeof(double));
    }

    // Inizializzazione della matrice A con valori casuali
    srand(time(NULL));
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            A[i][j] = rand() % 10 + 1; // valori casuali tra 1 e 10
        }
    }

    // Stampa della matrice A
    printf("La matrice A è:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            printf("%5.2f ", A[i][j]);
        }
        printf("\n");
    }

    // Allocazione della matrice somma finale (localSum)
    double **localSum = (double **)malloc(blockSize * sizeof(double *));
    for (i = 0; i < blockSize; i++) {
        localSum[i] = (double *)calloc(blockSize, sizeof(double));
    }

    // Allocazione delle sottomatrici
    //Allocazione tridimensionale 
    //vado a creare un array di nthreads elementi , dove ogni elemento è una matrice q*p
    double ***blocks = (double ***)malloc(nthreads * sizeof(double **));
    for (int t = 0; t < nthreads; t++) {
        blocks[t] = (double **)malloc(blockSize * sizeof(double *));
        for (i = 0; i < blockSize; i++) {
            blocks[t][i] = (double *)malloc(blockSize * sizeof(double));
        }
    }

    // Parallelizzazione
    #pragma omp parallel num_threads(nthreads)
    {
        int tid = omp_get_thread_num();
        int rowBlock = tid / q; //id fratto core riga
        int colBlock = tid % p; //id modulo core colonna
        int rowStart = rowBlock * blockSize;
        int colStart = colBlock * blockSize;

        // Estrazione del blocco locale
        for (int i = 0; i < blockSize; i++) {
            for (int j = 0; j < blockSize; j++) {
                blocks[tid][i][j] = A[rowStart + i][colStart + j];
            }
        }

        // Somma del blocco locale alla matrice somma finale
        #pragma omp critical
        {
            for (int i = 0; i < blockSize; i++) {
                for (int j = 0; j < blockSize; j++) {
                    localSum[i][j] += blocks[tid][i][j];
                }
            }
        }
    }

    // Stampa della matrice somma finale (localSum)
    printf("La matrice della somma finale è:\n");
    for (i = 0; i < blockSize; i++) {
        for (j = 0; j < blockSize; j++) {
            printf("%5.2f ", localSum[i][j]);
        }
        printf("\n");
    }

    // Deallocazione della matrice A, localSum e sottomatrici
    for (i = 0; i < M; i++) {
        free(A[i]);
    }
    free(A);

    for (i = 0; i < blockSize; i++) {
        free(localSum[i]);
    }
    free(localSum);

    for (int t = 0; t < nthreads; t++) {
        for (i = 0; i < blockSize; i++) {
            free(blocks[t][i]);
        }
        free(blocks[t]);
    }
    free(blocks);

    return 0;
}

/*
#pragma omp parallel num_threads(np * np)
    {
        int tid = omp_get_thread_num();
        int block_size = N / np; // Dimensione di ciascun blocco
        int row_block = tid / np; // Blocco di righe
        int col_block = tid % np; // Blocco di colonne

        // Calcolo su ogni blocco di righe-colonne
        for (int i = row_block * block_size; i < (row_block + 1) * block_size; i++) {
            for (int j = col_block * block_size; j < (col_block + 1) * block_size; j++) {
                // Esempio: Calcolo del prodotto puntuale tra elementi della matrice
                // result += matrix[i][j] * matrix[j][i]; 
                // Alternativamente, esegui qualsiasi operazione desiderata sui blocchi di righe-colonne
            }
        }
    }
*/
