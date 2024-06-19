/*  Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×M. Quindi, i core
devono collaborare per calcolare il minimo tra gli
elementi delle colonne di propria competenza e
conservare tale valore in un vettore c di dimensione M. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int** allocaMatrice(int N, int M);
void riempiMatrice(int **matrix, int N, int M);
void stampaMatrice(int **matrix, int N, int M);
void deallocaMatrice(int **matrix, int N);

int main() {
    int N, M, np;

    printf("Numero core: \n");
    scanf("%d", &np);

    printf("Dimensione N della matrice: \n");
    scanf("%d", &N);

    printf("Dimensione M della matrice: \n");
    scanf("%d", &M);

    int **matrix = allocaMatrice(N, M);
    riempiMatrice(matrix, N, M);

    printf("La matrice e': \n");
    stampaMatrice(matrix, N, M);

    // Alloco il vettore per salvare i min
    int *min = (int *)malloc(M * sizeof(int));

    // Inizializza il vettore dei min
    for(int j = 0; j < M; j++) {
        min[j] = matrix[0][j];
    }

    // Trova i minimi delle colonne
    #pragma omp parallel for shared(matrix, min) num_threads(np)
    for(int j = 0; j < M; j++) {
        for(int i = 1; i < N; i++) {
            if(matrix[i][j] < min[j]) {
                min[j] = matrix[i][j];
            }
        }
    }

    // Stampa il vettore di min
    printf("I minimi di ciascuna colonna sono: \n");
    for(int j = 0; j < M ; j++) {
        printf("%3.1d", min[j]);
    }
    printf("\n");

    // Dealloca la matrice
    deallocaMatrice(matrix, N);
    free(min);

    return 0;
}

int** allocaMatrice(int N, int M) {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = (int *)malloc(M * sizeof(int));
    return matrix;
}

void riempiMatrice(int **matrix, int N, int M) {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = rand() % 10; // Valori casuali tra 0 e 9
}

void stampaMatrice(int **matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void deallocaMatrice(int **matrix, int N) {
    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
}