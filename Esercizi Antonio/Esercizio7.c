/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1)Il core master deve generare una matrice A di dimensione NxM.
2) I coredevono collaborare per calcolare il minimo tra gli elementi delle colonne di propria competenza e conservare tale valore in un vettore c di dimensione M
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(){
    int N,M,i,j,nthreads;
    double **A;
    double *c;
    double t0,t1;

    printf("Inserire le dimensioni di N e M \n");
    scanf("%d %d",&N,&M);

    printf("Inserire il numero di threads da utilizzare:\n");
    scanf("%d",&nthreads);

    A=(double **)calloc(N,sizeof(double*));
    for(i=0;i<N;i++)
    {
        A[i]=(double *)calloc(M,sizeof(double));
    }


    c=(double *)calloc(M,sizeof(double));
    printf("La matrice A:\n");
    for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = rand() % 10 + 1;
                printf("A[%d][%d]=%lf\n",i,j,A[i][j]);
            }
        }
    t0=omp_get_wtime();
    #pragma omp parallel for shared(A,c) private(i,j) num_threads(nthreads)
    for (j = 0; j < M; j++) 
    { //per colonne
        double min = A[0][j];
        for (i = 1; i < N; i++) 
        {
            if (A[i][j] < min)
            { //calcolo del minimo
                min = A[i][j];
            }
        }
        c[j] = min;
    }

    t1=omp_get_wtime();
    printf("Il vettore dei minimi per colonna è:\n");
    for(i=0;i<M;i++)
    {
        printf("C[%d]=%lf\n",i,c[i]);
    }


    printf("Il tempo impiegato è: %lf\n",t1-t0);

    for(i=0;i<M;i++)
    {
    free(A[i]);
    }
    free(A);
    free(c);

    return 0;
}
