/* Implementazione di un algoritmo parallelo (np core)
per il calcolo degli elementi di un vettore c, i cui valori
sono ottenuti moltiplicando l’identificativo del core per
gli elementi di un vettore a di dimensione N, in
ambiente openMP */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void riempiVettore(double *vector, int n);
void stampaVettore(double *vector, int n);

int main() {
    int N, i;
    int np;

    printf("Numero core:");
    scanf("%d", &np);
     
    printf("Inserisci la dimensione N del vettore a: ");
    scanf("%d", &N);

    // Allocazione del vettore a
    double *a = (double *)malloc(N * sizeof(double));

    riempiVettore(a, N);

    stampaVettore(a, N);

    // Vettore c in cui verranno memorizzati i risultati
    double *c = (double *)malloc(N * sizeof(double));

    // Calcolo parallelo di c = id_core * a
    #pragma omp parallel for shared(c, a) private(i) num_threads(np)
    for (i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num();
        c[i] = thread_id * a[i];
    }

    // Stampa del vettore c
    printf("Il vettore c e' uguale a:\n");
    stampaVettore(c, N);

    free(a);
    free(c);

    return 0;
}

void riempiVettore(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }
}

void stampaVettore(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        printf("c[%d] = %f\n", i, vector[i]);
    }
}