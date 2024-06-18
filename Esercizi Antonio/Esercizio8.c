/*

Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1) Il core master deve generare una matrice A di dimensione N*M
2) Ogni core deve estrarre N/p colonne ed effettuare localmente la somma degli elementi delle sottomatrici estratte conservando il risultato in un vettore b di dimensione M.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int N,M,i,j,nthreads;
	double **A;
	double *b;
	double t0,t1;

	printf("Inserire il size della matrice\n");
	scanf("%d %d",&N,&M);

	printf("Inserire il numero di threads:\n");
	scanf("%d",&nthreads);

	A=(double **)calloc(N,sizeof(double*));
	for(i=0;i<N;i++)
	{
		A[i]=(double*)calloc(M,sizeof(double));
	}

	b=(double*)calloc(M,sizeof(double));

	printf("La matrice A ha i seguenti valori:\n");
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			A[i][j]=rand()%20+1;
			printf("A[%d][%d]=%lf\n",i,j,A[i][j]);
		}
	}

	t0=omp_get_wtime();
	#pragma omp parallel for shared(A,b) private(i,j) num_threads(nthreads)
	for(j=0;j<M;j++)
	{ //decomposizione per colonne
		double sum=0.0;
		for(i=0;i<N;i++)
		{
			sum+=A[i][j]; //somma di tutti gli elementi del blocco colonna per ogni core
		}
		b[j]=sum;
	}

	t1=omp_get_wtime();
	printf("il vettore risultante contenente la somma di ogni colonna è:\n");

	for(i=0;i<M;i++)
	{
		printf("b[%d]=%lf\n",i,b[i]);
	}

	printf("Il tempo impiegato è :%lf\n",t1-t0);

	free(b);

	for(i=0;i<N;i++)
	{
		free(A[i]);
	}

	free(A);
	return 0;
}

