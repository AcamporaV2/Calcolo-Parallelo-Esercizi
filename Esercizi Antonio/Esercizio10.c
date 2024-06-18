/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1)Il core master deve leggere una matrice di dimensione NxM
2)Quindi i core devono collaborare per sommare in parallelo i vettori corrispondenti alle righe dispari della matrice.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

	int i,j,N,M;
	double **A;
	int nthreads;
	double t0,t1;
	double *r;

	printf("Inserire il size della matrice (N-M)\n");
	scanf("%d %d",&N,&M);

	printf("Inserire il numero di threads :\n");
	scanf("%d",&nthreads);

	A=(double**)calloc(N,sizeof(double));
	for(i=0;i<N;i++){
	A[i]=(double*)calloc(M,sizeof(double));
	}

	r=(double*)calloc(M,sizeof(double));

	printf("Inserire i valori della matrice:\n");

	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			printf("A[%d][%d]=",i,j);
			scanf("%lf",&A[i][j]);
		}
	}

	t0=omp_get_wtime();

	#pragma omp parallel for shared(A,r) private(i,j) num_threads(nthreads)
	for(i=0;i<N;i++)
	{

		for(j=0;j<M;j++)
		{
			if(i%2!=0)
			{ //righe dispari
				#pragma omp atomic
				r[j]+=A[i][j]; //uso atomic perchè il risultato finale deve essere un solo array
				//frutto della somma tra gl array locali di ogni core
			}
		}
	}

	t1=omp_get_wtime();
	printf("Il vettore risultante r è:\n");

	for(i=0;i<M;i++)
	{
		printf("r[%d]=%lf\n",i,r[i]);
	}

	printf("Il tempo impiegato è : %lf\n",t1-t0);

	free(r);
	
	for(i=0;i<N;i++)
	{
		free(A[i]);
	}
	free(A);

	return 0;
}

