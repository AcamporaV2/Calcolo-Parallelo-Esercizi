#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Somma 2 vettori caso dove N non è divisibile per t

void  stampaVettore(float*, int, char[]);

int main() 
{
    int i, N, t, N_Loc, indice;

    int r, id, step; //Variabili aggiunte rispetto è quando è divisibile

    float *a, *b, *c;

    srand( time( NULL ) );



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


    #pragma omp parallel private (N_Loc, i, indice, id, step) shared (a, b, c, r)
    {
        t = omp_get_num_threads();
        id = omp_get_thread_num();
        N_Loc = N/t;

        r= N % t; //Calcolo resto della divisione

        //printf("sono %d, di %d: numeri %d, r=%d\n",id,t,N_Loc,r);

        if(id < r) //Se il core ha un identificativo minore del resto si deve occupare di calcolare un elemento in più del vettore soluzione C
        {
            N_Loc++;
            step=0;  
        } else
        {
            step = r;
        } //Step serve ad ogni core di sapere di quali elementi di A e B deve occuparsi

        printf("sono %d, di %d: numeri %d, r=%d, passo=%d\n",id,t,N_Loc,r,step);
        
        for(i=0; i < N_Loc; i++)
        {
            indice = i + N_Loc * omp_get_thread_num() + step;

            c[indice] = a[indice] + b[indice];
        }
    } //Fine direttiva 

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
