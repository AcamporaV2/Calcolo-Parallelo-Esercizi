/**
 * PROVA SCRITTA LABORATORIO TRACCIA 2: 29-06-2023
 * 
 * Implementare un programma parallelo per l'ambiente multicore 
 * con np unità processanti che impieghi la libreria OpenMP.
 * 
 * Il programma deve essere organizzato come segue:
 * 
 * 1. il master thread deve generare una matrice A,
 *    e leggere uno scalare alpha
 * 
 * 2. i core thread devono effettuare l’operazione B = A + alpha
 * 
 * 3. i core thread devono effettuare la trasposta di B
 * 
 * 4. i core thread dovevano stampare la loro porzione
 *    (quella che hanno trasposto) e il master thread
 *    doveva stampare il tempo di esecuzione
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void allocationMatrix( int*** matrix, int N, int M ) {
    *matrix = ( int** ) calloc( N, sizeof( int* ) );
    for ( int i = 0; i < N; i++ )
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );
}

void fillMatrix( int*** matrix, int N, int M ) {
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            ( *matrix )[i][j] = rand() % 10 + 1;
}

void printMatrix( int** matrix, int N, int M, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

void deallocationMatrix( int*** matrix, int N ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
}

int main(){

int i,j,nthreads,N,M;
int alpha;
int **A,**B,**T;
double t0,t1;

printf("Inserire le dimensioni del problema\n");
scanf("%d %d",&N,&M);

printf("Inserire il numero di threads da utilizzare:\n");
scanf("%d",&nthreads);

printf("Inserire il valore dello scalare alpha:\n");
scanf("%d",&alpha);

allocationMatrix(&A,N,M);
allocationMatrix(&B,M,N);
allocationMatrix(&T,N,M);
fillMatrix(&A,N,M);
printMatrix(A,N,M,"A");

t0=omp_get_wtime();
#pragma omp parallel for shared(A,alpha) private(i,j) num_threads(nthreads)
for(i=0;i<N;i++){
    for(j=0;j<M;j++){
        B[i][j]=A[i][j]+alpha; 
        T[j][i]= B[i][j];

 }
}
printMatrix(B,N,M,"B");
 #pragma omp parallel private(i,j) shared(T,N,M)
    {
        #pragma omp for
        for ( i = 0; i < N; i++ ) {
            printf( "\nThread %d trasponde: ", omp_get_thread_num() );
            for ( j = 0; j < M; j++ ) {
                // i core thread dovevano stampare la loro porzione
                printf( "%d ", T[j][i] );
            }
            printf( "\n" );
        }

}
t1=omp_get_wtime();
printMatrix(T,M,N,"Trasposta finale");
printf("Il tempo impiegato è : %lf\n",t1-t0);

deallocationMatrix(&A,N);
deallocationMatrix(&T,M);
deallocationMatrix(&B,N);


return 0;}
