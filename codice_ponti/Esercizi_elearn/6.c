/*  Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
una matrice A di dimensione N×N ed uno scalare alpha.
Quindi, i core devono collaborare per calcolare il
prodotto tra lo scalare alpha e la matrice A, sfruttando
una strategia di parallelizzazione che usi la
distribuzione per colonne della matrice A come
decomposizione del dominio. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int** allocaMatrice(int N);
void riempiMatrice(int **matrix, int N);
void stampaMatrice(int **matrix, int N);
void deallocaMatrice(int **matrix, int N);

int main() {
    int N, np;
    double alpha, t0, t1;

    printf("Numero core: \n");
    scanf("%d", &np);

    printf("Dimensione N della matrice: \n");
    scanf("%d", &N);

    printf("Inserisci lo scalare alpha: \n");
    scanf("%lf", &alpha);

    int **matrix = allocaMatrice(N);

    riempiMatrice(matrix, N);

    printf("La matrice e': \n");
    stampaMatrice(matrix, N);

    // Alloca la matrice per il risultato
    int **matrix2 = allocaMatrice(N);

    t0 = omp_get_wtime();

    // Prodotto scalare-matrice
    #pragma omp parallel for shared(matrix, matrix2, alpha) num_threads(np)
    for(int j = 0; j < N; j++) { // Distribuzione per colonne
        for(int i = 0; i <N; i++) {
            matrix2[i][j] = alpha * matrix[i][j];
        }
    }

    t1 = omp_get_wtime();

    // Stampa matrice risultante
    printf("La matrice risultato e': \n");
    stampaMatrice(matrix2, N);

    printf("IL tempo impiegato e': %lf\n", t1-t0);

    deallocaMatrice(matrix, N);
    deallocaMatrice(matrix2, N);

    return 0;
}

int** allocaMatrice(int N) {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = (int *)malloc(N * sizeof(int));
    return matrix;
}

void riempiMatrice(int **matrix, int N) {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10;
}

void stampaMatrice(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
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