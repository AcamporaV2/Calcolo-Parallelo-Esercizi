/* Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
una matrice di dimensione N×M, quindi i core devo
collaborare per sommare in parallelo i vettori
corrispondenti alle righe dispari della matrice. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void leggiMatrice(int **matrix, int N, int M);
void stampaMatrice(int **matrix, int N, int M);

int main() {
    int N, M, np;

    printf("Numero core: \n");
    scanf("%d", &np);

    printf("Dimensione N della matrice: \n");
    scanf("%d", &N);

    printf("Dimensione M della matrice: \n");
    scanf("%d", &M);

    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
    }

    // Leggi la matrice
    leggiMatrice(matrix, N, M);

    // Stampa la matrice letta
    printf("La matrice e': \n");
    stampaMatrice(matrix, N, M);

    // Allocazione del vettore per le somme delle righe dispari
    int *sums = (int *)malloc(N * sizeof(int));

    // Inizializzazione del vettore delle somme
    for (int i = 0; i < N; i++) {
        sums[i] = 0;
    }

    // Somma delle righe di indice dispari in parallelo con OpenMP
    #pragma omp parallel for num_threads(np) shared(matrix, sums, N, M)
    for (int i = 1; i < N; i += 2) { // i += 2 per accedere alle righe dispari (1, 3, 5, ...)
        for (int j = 0; j < M; j++) {
            #pragma omp atomic
            sums[i] += matrix[i][j];
        }
    }

    // Stampa le somme delle righe dispari
    printf("Le somme delle righe di indice dispari sono: \n");
    for (int i = 1; i < N; i += 2) {
        printf("%d\n", sums[i]);
    }

    // Deallocazione della matrice e del vettore delle somme
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(sums);

    return 0;
}

void leggiMatrice(int **matrix, int N, int M) {
    // Simuliamo la lettura di una matrice (ad esempio con valori casuali)
    srand(1234); // Inizializzazione del seed per valori riproducibili
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 10; // Valori casuali tra 0 e 9
        }
    }
}

void stampaMatrice(int **matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

