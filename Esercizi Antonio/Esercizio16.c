
/*
Implementare un programma parallelo per l'ambiente multicore con nqxnp unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve costruire una matrice A di dimensione MxN..
2)II blocchi della matrice A sono generati casualmente e in parallelo da ogni core.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int i,j,N,M,q,p;
    int nthreads;
    double **A;

    printf("Inserire il size del problema (M)(N):\n");
    scanf("%d %d",&M,&N);

    printf("Inserire il numero di core riga(q) e colonna(p)\n");
    scanf("%d %d",&q,&p);

    nthreads=q*p;

    A=(double**)calloc(M,sizeof(double*));
    for(i=0;i<M;i++){
        A[i]=(double*)calloc(N,sizeof(double));
    }

    int blockSize=N/q;
    srand(time(NULL));

    double t0=omp_get_wtime();
    #pragma omp parallel for collapse(2) private(i,j) shared(A) num_threads(nthreads)
    for (int blockRow = 0; blockRow < M; blockRow += blockSize) {
            for (int blockCol = 0; blockCol < N; blockCol += blockSize) {
                for (int i = blockRow; i < blockRow + blockSize && i < M; i++) {
                    for (int j = blockCol; j < blockCol + blockSize && j < N; j++) {
                        A[i][j]=rand()%10+1;
                    }
                }
            }
    }
    double t1=omp_get_wtime();
    printf("La matrice A ha i seguenti valori:\n");
    for(i=0;i<M;i++){
        for(j=0;j<N;j++)
        {
            printf("A[%d][%d]=%lf ",i,j,A[i][j]);
        }
    printf("\n");}

    printf("Il tempo impiegato è : %lf ",t1-t0);
    for(i=0;i<N;i++)
    {
        free(A[i]);
    }
     free(A);
    

    return 0;
 }
