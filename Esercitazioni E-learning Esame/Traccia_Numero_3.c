/*

Implementazione di un algoritmo parallelo (np core)
per il calcolo degli elementi di un vettore c, i cui valori
sono ottenuti moltiplicando l’identificativo del core per
gli elementi di un vettore a di dimensione N, in
ambiente openMP 

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void printArray(int * array, int size);
void fillArray(int * array, int size, int max_element);


#define N 10 //size vettore

int main() {
    int *a, *c;
    int np;


    printf("Numero di core:");
    scanf("%d", &np);

    printf("\nCore scelti %d\n", np);


    // Allocazione dinamica dei vettori a e c
    a = (int *)malloc(N * sizeof(int));
    c = (int *)malloc(N * sizeof(int));
    
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));
    
    // Riempimento del vettore a con numeri casuali
    fillArray(a, N, 10);  // Range massimo dei numeri casuali: 0-99
    
    // Utilizziamo OpenMP per parallelizzare il calcolo
    #pragma omp parallel for num_threads(np)
    for (int i = 0; i < N; i++) {
        int core_id = omp_get_thread_num();  // Ottieni l'identificativo del core
        c[i] = core_id * a[i];  // Calcola c[i] come identificativo del core * a[i]
    }
    
    // Stampiamo i vettori a e c risultanti
    printf("Vettore a:\n");
    printArray(a, N);
    
    printf("\nVettore c:\n");
    printArray(c, N);
    
    // Liberiamo la memoria allocata
    free(a);
    free(c);
    
    return 0;
}

void printArray(int * array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


//max element lo diamo noi in input
void fillArray(int * array, int size, int max_element) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % max_element;
    }
}
