#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//Somma N numeri Seconda strategia
//Uso del reduction

void printArray(int * array, int size);

int main() {
    srand(time(NULL));

    size_t i;
    int nloc, remainder, step, id, n_threads;
    unsigned long sum = 0;
    int * a;
    int size;


    printf("Inserire il size dell'array: ");
    scanf("%d", &size);

    a = calloc(size, sizeof(int));
    //FILL del vettore A
    for (size_t i = 0; i < size; ++i) {
        a[i] = rand() % 100 + 1;
    }
    
    puts("a:");
    printArray(a, size);
    putchar('\n');

    
    
    #pragma omp parallel shared(a, n_threads, size) private(i, nloc, remainder, step, id) reduction(+:sum)
    {
        id = omp_get_thread_num();
        n_threads = omp_get_num_threads();
        nloc = size / n_threads;
        remainder = size % n_threads;

        if (id < remainder) {
            nloc++;
            step = 0;
        } else {
            step = remainder;
        }

        for (i = 0; i < nloc; ++i) {
            size_t index = i + id * nloc + step;
            sum += a[index];
        }
    }

    printf("Global sum: %lu\n", sum);

    free(a);
  
    return 0;
}

void printArray(int * array, int size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
}
