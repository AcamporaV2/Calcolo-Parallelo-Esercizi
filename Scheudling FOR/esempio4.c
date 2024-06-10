#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

//Proviamo a migliorare usando la modalità dynamic. In questo modo ciascun thread ha una iterazione: quando questo termina gli verrà assegnata la successiva iterazione. 


//Ad ogni iterazione i thread aspettano un numero di secondi pari a l’indice dell’iterazione.

int main( )
{
  
  int n_threads, i;

    #pragma omp parallel for private(i) schedule(dynamic) num_threads(4)
    for ( i = 0; i < 16; i++ )
    {
        //aspetta un numero pari ad i secondi
        sleep(i);
        printf( "Il thread %d ha completato iterazione %d.\n", omp_get_thread_num() , i );
    }

    printf( "Tutti I thread hanno terminato!\n" );
  
    return 0;

}


/* La modalità dinamica è migliore quando le iterazioni possono richiedere tempi molto diversi. 
Tuttavia, esiste un’inevitabile sovraccarico nell’uso della pianificazione dinamica:
dopo ogni iterazione, i thread devono arrestarsi e ricevere un nuovo valore della variabile del ciclo da utilizzare per la successiva iterazione. 
Questo può provocare un evidente rallentamento.*/
