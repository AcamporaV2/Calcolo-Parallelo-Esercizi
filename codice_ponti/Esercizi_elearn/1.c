/*  Implementazione di un algoritmo parallelo (np core)
per il calcolo dell’operazione c=a+b con a,b vettori di
dimensione N, in ambiente openMP */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void riempiVettore(double *vector, int n);
void stampaVettore(double *vector, int n);

int main() {
    int N, i;
    printf("Inserisci la dimensione dei vettori: ");
    scanf("%d", &N);

    // Allocazione dei vettori
    double *a = (double *)malloc(N * sizeof(double));
    double *b = (double *)malloc(N * sizeof(double));
    double *c = (double *)malloc(N * sizeof(double));

    srand(time(NULL));

    // Generazione casuale dei valori dei vettori a e b
    riempiVettore(a, N);
    riempiVettore(b, N);

    // Calcolo parallelo di c = a + b
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Stampa risultato
    printf("Il vettore c e' uguale a:\n");
    stampaVettore(c, N);

    // Deallocazione dei vettori
    free(a);
    free(b);
    free(c);

    return 0;
}

void riempiVettore(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = (double)rand() / RAND_MAX * 10; // Genera un numero casuale tra 0 e 10
    }
}

void stampaVettore(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        printf("c[%d] = %f\n", i, vector[i]);
    }
}