#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Somma 2 vettori caso dove N è divisibile per t

void  stampaVettore(float*, int, char[]);

int main() 
{
    int i, N, t, N_Loc, indice;

    float *a, *b, *c;


    printf("Inserisci N \n");
    scanf("%d", &N);

    //Allocazione
    a = (float *)calloc(N, sizeof(float));
    b = (float *)calloc(N, sizeof(float));
    c = (float *)calloc(N, sizeof(float));

    //Valore vettori A e B
    for(i = 0; i< N; i++)
    {
        a[i] = rand() %100 + 1;
    }

    
    for(i = 0; i< N; i++)
    {
        b[i] = rand() %100 + 1;
    }

    //Stampa dei vettori
    stampaVettore(a, N, "Vettore A:");
    stampaVettore(b, N, "Vettore B:");


    //Questo si può fare così solo se il size è divisibile per il numero di thread (I thread della mia CPU sono 6)
    #pragma omp parallel private (N_Loc, i, indice) shared (a, b, c)
    {
        t = omp_get_num_threads();

        N_Loc = N/t;

        printf("Sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, N_Loc);

        for(i=0; i < N_Loc; i++)
        {
            indice = i + N_Loc * omp_get_thread_num();

            c[indice] = a[indice] + b[indice];
        }
    }

    stampaVettore( c, N, "Vettore C:" );

    printf("\n");

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
