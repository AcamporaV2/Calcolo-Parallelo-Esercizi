#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main()
{

int n_threads, id_thread, i;
// COMMENTATO: omp_set_num_threads(3);


//Se non specificato lo scheduling è STATIC, che potrebbe essere non ottimale per risolvere il tipo di problema che voglio risolvere
#pragma omp parallel for private(id_thread) num_threads(4)

for (i=0; i<=4; i++)
{

id_thread = omp_get_thread_num( ) ;

printf("Iterazione %d del thread %d\n", i, id_thread);

}
return 0;
}
