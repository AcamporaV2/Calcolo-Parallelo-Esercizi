/* Implementare un programma parallelo per l’ambiente
multicore con np unità processanti impieghi la libreria
OpenMP. Il programma deve essere organizzato come
segue: il core master deve leggere una matrice di
dimensione N×N, quindi i core devo collaborare per
ricopiare in parallelo gli elementi della diagonale
principale in un vettore di lunghezza N. Infine, i core
devono effettuare la somma degli elementi di tale
vettore in parallelo. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int** allocaMatrice(int N);
void riempiMatrice(int **matrix, int N);
void stampaMatrice(int **matrix, int N);
void deallocaMatrice(int **matrix, int N);

int main() {
    int N, i, sum = 0;
    int np;

    printf("Numero core:");
    scanf("%d", &np);

    printf("Inserisci la dimensione N della matrice: ");
    scanf("%d", &N);

    // Allocazione della matrice
    int **matrix = allocaMatrice(N);

    // Riempimento della matrice
    riempiMatrice(matrix, N);

    // Stampa la matrice
    stampaMatrice(matrix, N);

    // Alloca il vettore di dimensione N per contenere la diagonale principale
    int *vector = (int *)malloc(N * sizeof(int));

    // Copia diagonale nel vettore 
    #pragma omp parallel for shared(matrix, vector) private(i) num_threads(np)
    for (i = 0; i < N; i++) {
        vector[i] = matrix[i][i];
    }

    // Somma elementi del vettore
    #pragma omp parallel for reduction(+:sum) num_threads(np)
    for (i = 0; i < N; i++) {
        sum += vector[i];
    }

    printf("La somma degli elementi del vettore e': %d\n", sum);

    // Deallocazione della memoria
    deallocaMatrice(matrix, N);
    free(vector);

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
