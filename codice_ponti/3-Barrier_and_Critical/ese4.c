/* La direttiva 'barrier' viene utilizzata per sincronizzare i 
thread all'interno di un blocco parallelo. Quando un thread raggiunge
una direttiva barrier, si ferma e attende che tutti gli altri thread 
raggiungano la stessa direttiva prima di procedere. 
Questo garantisce che tutte le operazioni precedenti siano state 
completate prima che qualsiasi thread proceda oltre la barriera.

La direttiva critical viene utilizzata per creare una sezione critica 
di codice che può essere eseguita da un solo thread alla volta, 
garantendo che altre istruzioni critici non vengano eseguite 
contemporaneamente da altri thread. È utile quando più thread 
devono accedere e modificare una risorsa condivisa in modo sicuro.
*/

#include <stdio.h>
#include <omp.h>

int main(){
    int i;
    int thread_id;

    #pragma omp parallel
    {
        thread_id = omp_get_thread_num();

        //creiamo un loop cosicche' ogni thread stampi 'hello'
        for( int i = 0; i < omp_get_max_threads(); i++){
            if(i == omp_get_thread_num()){
                printf("Hello from process: %d\n", thread_id);
            }
            #pragma omp barrier
        }
    }
    return 0;
}
