/*
Implementazione di un algoritmo parallelo (np core)
per il calcolo dell'operazione c=alpha*a+b con a,b vettori di dimensione N e alpha uno scalare,
ovviamente, in ambiente openMP
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main(){

    int N,th,i;//dimvettore,numerothreads e iteratore
    double alpha,*a,*b,*c;//scalare e vettori
    double t0,t1;

    printf("Inserisci il valore di N\n");
    scanf("%d",&N);

    printf("Inserisci il numero di thread\n");
    scanf("%d",&th);

    a=(double*)calloc(N,sizeof(double));
    b=(double*)calloc(N,sizeof(double));
    c=(double*)calloc(N,sizeof(double));

    srand(time(NULL));

    for(i=0;i<N;i++)
    {
        a[i]=rand()%20+1;
        b[i]=rand()%20+1;

        printf("a[%d]=%f\n",i,a[i]);
        printf("\n");
        printf("b[%d]=%f\n",i,b[i]);
        printf("\n");
    }

    alpha=rand()%10+1;
    printf("Il valore dello scalare alpha è : %f\n",alpha);

    t0=omp_get_wtime();

    #pragma omp parallel for private(i) shared(a,b,c,alpha) num_threads(th)
    for(i=0;i<N;i++)
    {
        a[i] *= alpha;//prima parte del prodotto (alpha*a)
    }
    #pragma omp parallel for private(i) shared(a,b,c,alpha) num_threads(th)
    for(i=0;i<N;i++)
    {
        c[i]=a[i]+b[i];//seconda parte del prodotto 
    }
    t1=omp_get_wtime();

    printf("Il vettore risultante è:\n");

    for(i=0;i<N;i++)
    {
        printf("c[%d]=%f\n",i,c[i]);
    }
    printf("\n");
    
    printf("Il tempo impiegato dall'algoritmo è:%f\n",t1-t0);

    free(a);
    free(b);
    free(c);

    return 0;
}

