/*
Implementazione di un algoritmo parallelo (np core)
per il calcolo deli elementi di un vettore c, i cui valori
sono ottenuti molitplicando l'identificativo del core per
gli elementi di un vettore a di dimensione N
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
int main(){
    int i;//iteratore
    int N,th;
    double *a,*c;//vettori
    double t0,t1;

    printf("Inserisci il valore di N\n");
    scanf("%d",&N);

    printf("Inserisci il numero di threads\n");
    scanf("%d",&th);


    a=(double *)calloc(N,sizeof(double));
    c=(double *)calloc(N,sizeof(double));

    srand(time(NULL));

    for(i=0;i<N;i++)
    {

        a[i]=rand()%10+1;
        printf("a[%d]=%f\n",i,a[i]);

    }
    
    t0=omp_get_wtime();
    #pragma omp parallel for private(i) shared(a,c) num_threads(th)

    for(i=0;i<N;i++)
    {
    c[i]=a[i]*omp_get_thread_num();
    }

    t1=omp_get_wtime();
    printf("I valori del vettore c sono:\n");

    for(i=0;i<N;i++)
    {
        printf("c[%d]=%f\n",i,c[i]);
    }
    printf("Il tempo impiegato dall'algoritmo è: %f",t1-t0);


    free(a);
    free(c);

    return 0;
}

