#include <stdio.h>
#include <omp.h>

int main() {
    // Imposta il numero di thread OpenMP
    omp_set_num_threads(4);
    
    // La direttiva pragma indica al compilatore di eseguire il blocco di codice in parallelo
    #pragma omp parallel
    {
        // Ogni thread in parallelo stampa un messaggio che include il suo numero di thread
        printf("Hello from process: %d\n", omp_get_thread_num());
    }

    return 0; 
}
