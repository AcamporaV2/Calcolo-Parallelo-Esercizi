#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Prodotto Scalare di due Vettori A e B in una variabile

void  stampaVettore(float*, int, char[]);

int main(){

    int i, N;
    float *a ,*b, result;

    srand( time( NULL ) );

    printf( "\nInserire N: " );
    scanf( "%d", &N );
    
    // allocazione
    a = ( float* ) calloc( N, sizeof( float ) );
    b = ( float* ) calloc( N, sizeof( float ) );

    //riempimento Vettori A e B
    for(i = 0; i < N; i++)
    {
        a[i] = rand() % 100 + 1;
    }
    
    for(i = 0; i < N; i++)
    {
        b[i] = rand() % 100 + 1;
    }

    stampaVettore(a, N, "Vettore A:");
    stampaVettore(b, N, "Vettore B:");

    #pragma omp parallel for private(i) shared(a,b) reduction(+:result)
        for(i = 0; i < N; i++)
        {
            result += a[i]*b[i];
        }

    printf("\n Risultato: %f\n", result);

    free(a);
    free(b);

    return 0;
}


//Funzione per la stampa del vettore
void stampaVettore( float* a, int N, char name[] ) {

    printf( "\n%s:\n", name );

    for ( int i = 0; i < N; i++ )
    {        
        printf( "%f ", a[i] );
        printf( "\n" );
    }
}
