
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

//Prodotto Matrice Vettore seconda strategia(blocchi colonna)


//Rispetto alla prima invertiamo qui nei define
#define N 8
#define M 16
#define VECTORSIZE N  //SECONDA STRATEGIA
#define RESULTVECTORSIZE M //SECONDA STRATEGIA
#define MAXVALUE 9

void AllocazioneMatriceVettore( int***, int**, int** );
void RiempiMatriceVettore( int***, int**, int** );
void StampaMatrice( int**, char[] );
void StampaVettore( int*, int, char[] );
void DeallocaMatriceVettore( int***, int**, int** );

int main()
{

    int** matrice;
    int* vettore;
    int* risultato;
    int i,j;

    srand(time(NULL));

    AllocazioneMatriceVettore(&matrice, &vettore, &risultato);
    RiempiMatriceVettore( &matrice, & vettore, &risultato);


    StampaMatrice(matrice, "Matrice Iniziale:");
    StampaVettore(vettore, VECTORSIZE, "Vettore Iniziale");

    //Qui J e I sono state invertite tranne che nella matrice nel +=, rivedi con la prima strategia se ti confondi
    #pragma omp parallel for default(none) shared (matrice, vettore, risultato) private(i,j)
    for( j= 0; j < M; j++)
    {
        for (i=0; i < N; i++)
        {
            risultato[j] += matrice[i][j] * vettore[i];
        }
    }

    StampaVettore(risultato, RESULTVECTORSIZE, "Vettore risultato:");
    DeallocaMatriceVettore( &matrice, &vettore, &risultato);

    return 0;
}


void AllocazioneMatriceVettore( int*** matrix, int** vector, int** result ) {
    // Allocazione della memoria per le righe della matrice
     *matrix = ( int** ) calloc( N, sizeof( int* ) );

    // Allocazione della memoria per ogni riga della matrice
    for ( int i = 0; i < N; i++ ){
        
        ( *matrix )[i] = ( int* ) calloc( M, sizeof( int ) );

    }
    // Allocazione della memoria per il vettore iniziale
    *vector = ( int* ) calloc( VECTORSIZE, sizeof( int ) );
    
    // Allocazione della memoria per il vettore risultato
    *result = ( int* ) calloc( RESULTVECTORSIZE, sizeof( int ) );
}

//Riempimento della matrice, del vettore iniziale e vettore risultato
void RiempiMatriceVettore( int*** matrix, int** vector, int** result ) {
    //Matrice
    for ( int i = 0; i < N; i++ )
    {
        for ( int j = 0; j < M; j++ )
        {
            ( *matrix )[i][j] = rand() % MAXVALUE + 1;
        }
    }
    //Vettore iniziale
    for ( int i = 0; i < VECTORSIZE; i++ )
    {
        ( *vector )[i] = rand() % MAXVALUE + 1; 
    }
    //Vettore risultato
    for ( int i = 0; i < RESULTVECTORSIZE; i++ )
    {
        ( *result )[i] = 0;
    }
}


//Stampa della matrice
void StampaMatrice( int** matrix, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ )
            printf( "%d    ", matrix[i][j] );
        printf( "\n" );
    }
}

//Stampa vettore
void StampaVettore( int* vector, int n, char name[] ) {
    printf( "\n%s: ", name );
    for ( int i = 0; i < n; i++ )
        printf( "%d ", vector[i] );
    printf( "\n" );
}


//Deallocazione in memoria della matrice, vettore iniziale e vettore risultato
void DeallocaMatriceVettore( int*** matrix, int** vector, int** result ) {
    for ( int i = 0; i < N; i++ )
        free( ( *matrix )[i] );
    free( *matrix );
    free( *vector );
    free( *result );
}
