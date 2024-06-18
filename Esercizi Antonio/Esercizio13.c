/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti.
Il programma deve essere organizzato come segue:
1)Il core master deve generare una matrice A di dimensione NxM.
2)I core devono collaborare per valutare il minimo valore tra gli elementi di A.
3)successivamente, costruire la matrice B i cui elementi sono dati dalla
somma del minimo per gli elementi di posto corrispondente della matrice di partenza.
(Cosa significa quest'ultimo punto ??? E' uno strano modo per dire che la matrice risultante
è data dalla matrice originale sommata elemento per elemento per il minimo ???)
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int main(){

    int i,j,nthreads,N,M;
    double **A,**B;
    double t0,t1;
    double minimo;

    printf("Inserire il valore di N e M\n");
    scanf("%d %d",&N,&M);

    printf("Inserire il numero di threads da utilizzare:\n");
    scanf("%d",&nthreads);

    A=(double**)calloc(N,sizeof(double*));
    for(i=0;i<N;i++)
    {
        A[i]=(double*)calloc(M,sizeof(double));
    }

    B=(double**)calloc(N,sizeof(double*));
    for(i=0;i<N;i++)
    {
        B[i]=(double*)calloc(M,sizeof(double));
    }

    srand(time(NULL));

    //riempimento con numeri casuali matrice A
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            A[i][j]=rand()%20+1;
        }
    }

    printf("gli elementi della matrice A sono:\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            printf("A[%d][%d]=%lf ",i,j,A[i][j]);
        }
        printf("\n");
    }
        t0=omp_get_wtime();
        minimo=A[0][0];

    #pragma omp parallel for reduction(min:minimo) shared(A) private(i,j) num_threads(nthreads) 
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(A[i][j]<minimo)
            {
                minimo=A[i][j];
            }
        }
    }
    printf("Il minimo è:%lf\n",minimo);

    #pragma omp parallel for shared(A,B) private(i,j) num_threads(nthreads)
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            B[i][j]=minimo+A[i][j];
        }
    }
    t1=omp_get_wtime();
    printf("La matrice risultante B è:\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
        printf("B[%d][%d]=%lf ",i,j,B[i][j]);
        }
        printf("\n");
    }

    printf("Il tempo impiegato è %lf\n",t1-t0);

    return 0;
}