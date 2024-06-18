/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1)Il core master deve generare due vettori casuali di dimensione N
2)Ogni core deve sommare ad ogni elemento dei due vettori il proprio identificativo e collaborare alla costruzione di una matrice NxM, con
M=2np le cui colonne a due a due, sono i vettori ottenuti nella fase precedente:
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main(){
	int N,M,i,j,nthreads;
	double *a,*b,**C;
	double t0,t1;

	printf("Inserire la dimensione del vettore(n)\n");
	scanf("%d",&N);

	printf("Inserire il numero di threads da utilizzare:\n");
	scanf("%d",&nthreads);

	M=2*nthreads;

	b=(double*)calloc(N,sizeof(double));
	a=(double*)calloc(N,sizeof(double));

	C=(double**)calloc(N,sizeof(double*));
	for(i=0;i<N;i++)
	{
		C[i]=(double*)calloc(M,sizeof(double));
	}

	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		a[i]=rand()%50+1;
		b[i]=rand()%20+1;
	}
	printf("Il vettore A ha i seguenti elementi:\n");
	for(i=0;i<N;i++)
	{
		printf("A[%d]=%lf\n",i,a[i]);
	}

	printf("Il vettore B ha i seguenti elementi:\n");
	for(i=0;i<N;i++)
	{
		printf("B[%d]=%lf\n",i,b[i]);
	}
	t0=omp_get_wtime();
	#pragma omp parallel for private(i,j) shared(a,b,C) num_threads(nthreads)
	for(i=0;i<N;i++)
	{
		a[i]+=omp_get_thread_num(); //somme con id core
		b[i]+=omp_get_thread_num();
	}

	#pragma omp parallel for  private(i,j) shared(a,b,C) num_threads(nthreads)
	for(j=0;j<M;j++)
	{ //accesso per colonne

		for(i=0;i<N;i++)
		{
			if(j%2==0)
			{ //se l'indice colonna è pari
			C[i][j]=a[i]; //inserisco a in quella colonna
			} else{
			C[i][j]=b[i]; //altrimenti inserisco b
			}
		}
	}

	t1=omp_get_wtime();
	printf("La matrice risultante è:\n");

	for(i=0;i<N;i++)
	{

		{
		for(j=0;j<M;j++)
		printf("C[%d][%d]=%lf\n",i,j,C[i][j]);
		}
	}

	printf("Il tempo impiegato è:%lf\n",t1-t0);

	free(b);
	free(a);
	for(i=0;i<N;i++)
	{
		free(C[i]);
	}
	free(C);


	return 0;

}
