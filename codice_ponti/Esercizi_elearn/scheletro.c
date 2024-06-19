#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Dichiarazione delle funzioni
int** allocaMatrice(int N, int M);
void riempiMatrice(int **matrix, int N, int M);
void stampaMatrice(int **matrix, int N, int M, char *name);
int* allocaVettore(int N);
void deallocaMatrice(int **matrix, int N);
void deallocaVettore(int *vector);

int main() {
    int N, M, np;

    // Input dimensioni matrice e numero di core
    printf("Inserisci il numero di righe (N): ");
    scanf("%d", &N);

    printf("Inserisci il numero di colonne (M): ");
    scanf("%d", &M);

    printf("Inserisci il numero di core: ");
    scanf("%d", &np);

    // Allocazione e inizializzazione della matrice
    int **matrix = allocaMatrice(N, M);
    riempiMatrice(matrix, N, M);

    // Stampa della matrice iniziale
    stampaMatrice(matrix, N, M, "Matrice iniziale");

    // Allocazione del vettore di dimensione N per contenere la diagonale principale
    int *vector = allocaVettore(N);

    // Deallocazione della matrice
    deallocaMatrice(matrix, N);

    // Deallocazione del vettore
    deallocaVettore(vector);

    return 0;
}

// Funzione per l'allocazione di una matrice di dimensione N x M
int** allocaMatrice(int N, int M) {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = (int *)malloc(M * sizeof(int));
    return matrix;
}

// Funzione per il riempimento casuale di una matrice di dimensione N x M
void riempiMatrice(int **matrix, int N, int M) {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = rand() % 10; // Valori casuali tra 0 e 9
}

// Funzione per la stampa di una matrice di dimensione N x M
void stampaMatrice(int **matrix, int N, int M, char *name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

// Funzione per l'allocazione di un vettore di dimensione N
int* allocaVettore(int N) {
    int *vector = (int *)malloc(N * sizeof(int));
    return vector;
}

// Funzione per la deallocazione di una matrice di dimensione N x M
void deallocaMatrice(int **matrix, int N) {
    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
}

// Funzione per la deallocazione di un vettore di dimensione N
void deallocaVettore(int *vector) {
    free(vector);
}