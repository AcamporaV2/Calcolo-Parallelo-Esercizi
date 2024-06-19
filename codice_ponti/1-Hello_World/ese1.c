#include <stdio.h>
#include <omp.h> // Include la libreria OpenMP

int main() {
    // Stampa un messaggio di saluto dal thread OpenMP corrente
    printf("Hello from process: %d\n", omp_get_thread_num());

    return 0; // Restituisce 0 per indicare che il programma è terminato correttamente
}
