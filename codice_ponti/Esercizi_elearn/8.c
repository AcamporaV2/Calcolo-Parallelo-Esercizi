/* Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×M. Quindi, ogni core
deve estrarre N/p colonne ed effettuare localmente la
somma degli elementi delle sottomatrici estratte,
conservando il risultato in un vettore b di dimensione
M. */

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

    // Alloca il vettore per salvare le somme
    int *sums = (int *)malloc(M * sizeof(int));

    // Inizializza il vettore delle somme
    for (int j = 0; j < M; j++) {
        sums[j] = 0;
    }

    // Trova le somme delle colonne
    #pragma omp parallel for num_threads(np) shared(matrix, sums, N, M)
    for (int j = 0; j < M; j++) {
        int local_sum = 0;
        int id = omp_get_thread_num(); // Ottiene l'ID del thread
        for (int i = 0; i < N; i++) {
            local_sum += matrix[i][j];
        }
        sums[j] = local_sum;
        printf("Sono core %d \n", id); // Stampa l'ID del thread
    }

    // Stampa il vettore delle somme
    printf("Le somme di ciascuna colonna sono: \n");
    for (int j = 0; j < M; j++) {
        printf("%d ", sums[j]);
    }
    printf("\n");

    // Dealloca la matrice
    deallocaMatrice(matrix, N);
    free(sums);

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