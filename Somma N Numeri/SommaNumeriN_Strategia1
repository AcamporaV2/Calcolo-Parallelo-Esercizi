#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Somma N numeri di un vettore STRATEGIA 1
//Faccio direttamente la versione con il resto


void  stampaVettore(float*, int, char[]);

int main(){

    int i, N, t, N_Loc, rest, id, step;
    float *a, sum, sumtot;
    sumtot = 0;

    srand(time(NULL));

    printf("Inserisci N:");
    scanf("%d", &N);
    printf("\n");

    a = (float*) calloc(N, sizeof(float));

    for (i = 0; i < N; i++)
    {
        a[i] = rand() % 100 + 1;
    }

    stampaVettore(a, N, "Vettore A:");

    //Comprende i casi in cui N non è divisibile per t
    #pragma omp parallel private (sum, N_Loc, i, step, id) shared(sumtot, rest)
    {
        t = omp_get_num_threads();
        id = omp_get_thread_num();
        N_Loc = N/t;
        rest = N%t;

        if (id < rest)
        {
            N_Loc++;
            step = 0;
        } else {
            step = rest;
        }

        printf( "sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, N_Loc );
        
        sum = 0;

        for(i = 0; i < N_Loc; i++)
        {
            sum = sum + a[i + N_Loc * omp_get_thread_num() + step];
        }

        sumtot += sum;

    } //Fine direttiva

    printf("\nSomma totale: %f\n", sumtot);

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
