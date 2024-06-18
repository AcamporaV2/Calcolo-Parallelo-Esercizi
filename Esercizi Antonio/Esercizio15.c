/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve leggere un vettore a di dimensione M, e uno scalare alpha.
2)I core devono collaborare per costruire una matrice A, di dimensione MxM
la cui diagonale principale ha per elementi quelli del vettore a moltiplicati per lo scalare.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main(){
    int i,j,M,alpha,nthreads;
    double *a;
    double t0,t1;

    printf("Inserire il numero di threads:\n");
    scanf("%d",&nthreads);

    printf("Inserire il size (M)\n");
    scanf("%d",&M);
    srand(time(NULL));
    a=(double*)calloc(M,sizeof(double));
    /*
    for(i=0;i<M;i++){
        scanf("%lf",&a[i]);
    }
    */
    for(i=0;i<M;i++){
        a[i]=rand()%10+1;
    }

    printf("Il vettore A:\n");
    for(i=0;i<M;i++){
        printf("a[%d]=%lf ",i,a[i]);
    }printf("\n");

    printf("Inserisci il valore dello scalare alpha:\n");
    scanf("%lf",&alpha);


    double **A=(double**)calloc(M,sizeof(double*));
            for(i=0;i<M;i++){
                A[i]=(double*)calloc(M,sizeof(double));
            }
    t0=omp_get_wtime();
    #pragma omp parallel for shared(a,alpha) private(i,j) num_threads(nthreads)
    for(i=0;i<M;i++){
        for(j=0;j<M;j++){
            if(i==j){
                A[i][j]=a[i]*alpha;
            }else{
                A[i][j]=1;
            }
            
        }
    }
    t1=omp_get_wtime();
    printf("La matrice A ha i seguenti elementi :\n");
    for(i=0;i<M;i++){
        for(j=0;j<M;j++){
            printf("A[%d][%d]=%lf ",i,j,A[i][j]);}
    printf("\n");}

    printf("Il tempo impiegato è: %lf",t1-t0);

    free(a);
    for(i=0;i<M;i++){
        free(A[i]);
    }
    free(A);

    return 0;

}