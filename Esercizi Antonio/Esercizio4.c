/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1) Il core master deve leggere una matrice di dimensione NxN
2)i core devono collaborare per ricopiare gli elementi della diagonale principale in un vettore di lunghezza N
3)Infine, i core devono effettuare la somma degli elementi di tale vettore in parallelo
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
int main(){
	int N,nthreads,i,j; //size del problema, numero di threads, iteratori i e j
	double **A; //matrice A
	double *b;//vettore b
	double sumtot=0.0,t0,t1; //variabile per salvare la somma degli elementi del vettore, variabili per prendere il tempo dell'algoritmo
	//1)
	printf("Inserisci il size N della matrice\n");//inserimento da tastiera del size
	scanf("%d",&N);

	printf("Inserire il numero di threads da utilizzare:\n");//inserimento da tastiera del numero di threads
	scanf("%d",&nthreads);

	A=(double **)calloc(N,sizeof(double *));//allocazione dinamica della matrice A
	for(i=0;i<N;i++)
	{
		A[i]=(double*)calloc(N,sizeof(double));
	}

	b=(double*)calloc(N,sizeof(double));//allocazione dinamica del vettore b

	srand(time(NULL));

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			A[i][j]=rand()%20+1; //riempimento della Matrice A con numeri casuali da 1 a 20
		}
	}

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("A[%d][%d]=%f\n",i,j,A[i][j]); //stampa della matrice A
		}
	}


	//2)
	t0=omp_get_wtime();//prendo il tempo

	#pragma omp parallel for private(i,j) shared(A,b) num_threads(nthreads) reduction(+:sumtot)
	for(i=0;i<N;i++)
	{
		b[i]=A[i][i]; //salvo la diagonale principale
		//3)
		sumtot+=b[i]; //effettuo la somma degli elementi
		//operazione di somma quindi reduction
	}

	t1=omp_get_wtime();//prendo il tempo al termine della direttiva parallela
	printf("Il risultato totale è  %f\n",sumtot);//stampo la somma totale
	printf("Il tempo impiegato : %f\n",t1-t0); //stampo il tempo impiegato

	free(b);//dealloco il vettore b

	for(i=0;i<N;i++)
	{
		free(A[i]);//dealloco la matrice A
	}
	free(A);

	return 0;
}

