/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. 
Il programma deve essere
organizzato come segue: 

1)il core master deve leggere quattro valori scalari a0, a1, a2, a3, 

2)quindi i core devono collaborare per costruire un vettore di dimensione 4np
i cui elementi sono dati dalla somma di tali valori con il
proprio identificativo

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void printVector( int*, int, char[] );



int main()
{
    int *Vettore;
    int a0,a1,a2,a3;
    int np;
    size_t i;

    printf("dammi numero core ");
    scanf("%d", &np);

    int sizeVettore = 4 * np;

    Vettore = (int *) calloc(sizeVettore, sizeof(int));

    #pragma omp master
    {
        printf("Dammi lo scalare a0 ");
        scanf("%d",&a0);
        
        printf("Dammi lo scalare a1 ");
        scanf("%d",&a1);
        
        printf("Dammi lo scalare a2 ");
        scanf("%d",&a2);
        
        printf("Dammi lo scalare a3 ");
        scanf("%d",&a3);
    }

    printf("1) %d \n 2) %d\n 3) %d\n 4) %d\n", a0,a1,a2,a3);

    #pragma omp parallel for shared(Vettore,a0,a1,a2,a3) private(i) num_threads(np)
    for(i=0; i < sizeVettore; i++)
    {
        int id = omp_get_thread_num();

        Vettore[i] = a0 + a1 + a2 + a3 + id;
    }


    printVector(Vettore, sizeVettore, "Vettore");

}


void printVector( int* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%d ", a[i] );
    printf( "\n" );
}