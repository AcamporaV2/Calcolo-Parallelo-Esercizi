/*
Lo work-sharing è una tecnica utilizzata nella programmazione 
parallela per distribuire il lavoro tra più thread o processi 
in modo equo e efficiente. In pratica, questa tecnica divide un 
compito computazionale in parti più piccole e assegna ciascuna
parte a un thread o processo separato per essere eseguita 
in parallelo. 
*/

/*Programma che sommi tutti i numeri compresi tra 1 e 1000 */

#include <stdio.h>
#include <omp.h>

int main() {
    int totSum = 0, partSum = 0; // Inizializziamo la somma totale e parziale

    #pragma omp parallel private(partSum) // Ogni thread ha la propria somma parziale
    {
        partSum = 0; // Inizializziamo la somma parziale per ciascun thread

        #pragma omp for
        for (int i = 1; i <= 1000; i++) {
            partSum += i; // Calcoliamo la somma parziale per ciascun thread
        }

        #pragma omp critical
        {
            // Aggiungiamo la somma parziale di ogni thread alla somma totale
            totSum += partSum;
        }
    }

    printf("La somma totale: %d\n", totSum);

    return 0;
}
