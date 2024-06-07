#include <stdio.h>
#include <omp.h>

#define N 100000000

int main(int argc, char **argv){

    long int i;
    double x, dx, f, sum, pi;

    sum = 0.0;

    dx = 1.0/ (double) N;

    printf("Numero Intervalli: %ld\n", N);


    #pragma omp parallel for private(x,f,i) shared(dx) reduction(+:sum)
    
    for (i = 1; i<= N; i++)
        {
            x = dx * ( (double) (i - 0.5) );
            f = 4.0 / (1.0 + x * x);
            sum += f;
        }

    pi = dx * sum;
    printf("PI %.20f\n", pi);

    return 0;


    
}
