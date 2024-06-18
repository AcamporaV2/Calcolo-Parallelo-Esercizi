/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1) Il core master deve leggere una matrice di dimensione NxN
2) Ogni core deve estrarre n/np righe e calcolare il prodotto puntuale tra i vettori corrispondenti alle righe estratte.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(){
int N,nth,i,j;
double **A;


printf("Inserisci il size N del problema:\n");
scanf("%d",&N);

printf("Inserisci il numero di threads da utilizzare:\n");
scanf("%d",&nth);

A=(double **)calloc(N,sizeof(double *));
for(i=0;i<N;i++){
A[i]=(double)calloc(N,sizeof(double));
}

srand(time(NULL));
for(i=0;i<N;i++){
A[i]=rand()%10+1;
printf("A[%d][%d]=%f\n",i,j,A[i][j]);
}

//TODO punto 2 impossibile da comprendere cosa si deve fare
#pragma omp parallel num_threads(nth) private(i, j)
    {
        int tid = omp_get_thread_num();
        int start = (tid * N) / nth;
        int end = ((tid + 1) * N) / nth;

        for (i = start; i < end; i++) {
        for(j=0;j<N;j++){

        }


}
*/
