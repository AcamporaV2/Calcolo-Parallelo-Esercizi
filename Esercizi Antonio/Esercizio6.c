/*

Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1) Il core master deve leggere una matrice A di dimensione NxN ed uno scalare alpha;
2)I core devono collaborare per calcolare il prodotto tra lo scalare alpha e la matrice A, sfruttando una strategia di parallelizzazione
che usi la distribuzione per colonne della matrice A come decomposizione del dominio.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(){
    int N,nthreads,i,j;
    double alpha;
    double **A;
    double t0,t1;

    printf("Inserire la dimensione della matrice\n");
    scanf("%d",&N);

    printf("Inserire il numero di threads da utilizzare\n");
    scanf("%d",&nthreads);

    A=(double **)calloc(N,sizeof(double *));
    for(i=0;i<N;i++)
    {
        A[i]=(double *)calloc(N,sizeof(double));
    }

    printf("Inserire i valori della matrice :\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("A[%d][%d]=",i,j);
            scanf("%lf",&A[i][j]);
        }
    }

    printf("La matrice inserita è:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%lf ", A[i][j]);
            }
            printf("\n");
        }

    printf("Inserire il valore dello scalare alpha\n");
    scanf("%lf",&alpha);

    t0=omp_get_wtime();

    #pragma omp parallel for shared(A,alpha) private(i,j) num_threads(nthreads)
    for(j=0;j<N;j++)
    { //decomposizione matrice per colonne
        for(i=0;i<N;i++)
        {
            A[i][j]*=alpha;
        }	
    }

    t1=omp_get_wtime();
    printf("La matrice Risultato è:\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++){
        printf("A[%d][%d]=%lf\n",i,j,A[i][j]);
        }
    }
    printf("Il tempo impiegato : %lf\n",t1-t0);

    for(i=0;i<N;i++)
    {
        free(A[i]);
    }

    free(A);

    return 0;
}
