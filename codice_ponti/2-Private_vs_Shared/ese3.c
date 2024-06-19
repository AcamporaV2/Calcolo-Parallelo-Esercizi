/*
In OpenMP, le variabili private e shared sono utilizzate per 
definire come le variabili vengono gestite e condivise tra i 4
   Le variabili condivise (shared) sono accessibili e modificabili 
   da tutti i thread nel blocco parallelo.
   Ogni thread condivide la stessa istanza della variabile condivisa.
   Le modifiche effettuate da un thread sono visibili agli altri thread.
   
   Le variabili private sono invece variabili locali a ciascun thread.
   Ogni thread ha una propria copia indipendente della variabile.
   Le modifiche alla variabile all'interno del blocco parallelo non 
   influenzano altre parti del codice.
   
   Utilizzare le variabili private e condivise in modo appropriato 
   permette di controllare l'accesso e le modifiche alle variabili 
   da parte dei thread, garantendo una corretta esecuzione parallela 
   del codice.
*/

#include <stdio.h>
#include <omp.h>

int main(){

    int thread_id;

    #pragma omp parallel private(thread_id)//ogni task avra' un unico thread id
    {
        thread_id = omp_get_thread_num();
        printf("Hello from process: %d\n", thread_id);
    }
}