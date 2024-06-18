/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve leggere quattro valori scalari a0,a1,a2,a3,
2)I core devono collaborare per costruire un vettore di dimensione 4np
i cui elementi sono dati dalla somma di tali valori con il proprio identificativo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int main(){
    int i,nthreads;
    double *a;
    double *b;

    a=(double*)calloc(4,sizeof(double));
    printf("Inserimento dei 4 scalari:\n");
    for(i=0;i<4;i++){
        printf("a[%d]= \n",i);
        scanf("%lf",&a[i]);
    }

    printf("Inserire il numero di threads da utilizzare:\n");
    scanf("%d",&nthreads);

    b=(double*)calloc(4*nthreads,sizeof(double));
    double t0=omp_get_wtime();
    #pragma omp parallel for num_threads(nthreads)
    
    for(i=0;i<4*nthreads;i++){
        int id=omp_get_thread_num();
        b[i]=id+a[i%4];
        
    }
    double t1=omp_get_wtime();
    printf("Il vettore risultante b è:\n");
    for(i=0;i<4*nthreads;i++)
    {
        printf("b[%d]=%lf\n",i,b[i]);
    }
    printf("Il tempo impiegato è: %lf\n",t1-t0);
    free(a);
    free(b);

    return 0;
}