/*

Implementare un programma parallelo per l’ambiente multicore 
con np unità processanti che impieghi la libreria OpenMP. 

Il programma deve essere organizzato come segue: 
1)il core master deve leggere un vettore a, di dimensione N 
ed uno scalare beta. 

2)Quindi i core devo collaborare per verificare se nel vettore 
esista almeno un elemento uguale al valore beta. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void printVector( int*, int, char[] );


int main()
{
    int *vettore;
    int N;
    int beta, i;
    int np;
    int contatore = 0;
    srand(time(NULL));

    printf("dammi size N ");
    scanf("%d", &N);

    printf("dammi numero core ");
    scanf("%d", &np);

    #pragma omp master
    {
        printf("Dammi uno scalare ");
        scanf("%d", &beta);

        vettore = (int*) calloc(N, sizeof(int));

        //fill vettore
        for (i=0; i < N; i++)
        {
            vettore[i] = rand() % 6 + 1;
        }
    }

    printVector(vettore, N, "Vettore");
    
    #pragma omp parallel for shared(vettore, beta) private(i) num_threads(np)
    for (i = 0; i < N; i++)
    {
        if (vettore[i] == beta)
        {
            contatore++;
        }
    }

    printf("ci sono ben %d valori uguali nel vettore\n", contatore);

}

void printVector( int* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%d ", a[i] );
    printf( "\n" );
}