/*

Implementare un programma parallelo per l’ambiente multicore con 
np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve leggere un vettore a, di dimensione M, 
e uno scalare alpha. 

2)Quindi i core devono collaborare per costruire una matrice A,
di dimensione M×M, la cui diagonale principale ha per
elementi quelli del vettore a moltiplicati per lo scalare
alpha


*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
void allocationMatrix(int***, int, int);
void fillMatrix(int***, int, int);
void printMatrix(int**, int, int, char[]);
void deallocationMatrix(int***, int);
void printVector( int*, int, char[] );


int main()
{
    int **Matrice;
    int *Vettore_A;
    int M;
    int alpha;
    int i,j, num_core;

    printf("Inserire numero core: ");
    scanf("%d", &num_core);

    printf("Inserisci Scalare alpha:");
    scanf("%d", &alpha);

    printf("insrire size M:");
    scanf("%d", &M);

    srand(time(NULL));
    Vettore_A = (int*)calloc(M, sizeof(int));

    for(i=0; i< M;i++)
    {
        Vettore_A[i] = rand() % 6+2;
    }

    printVector(Vettore_A, M, "Vettore");
    allocationMatrix(&Matrice, M, M);

    #pragma omp parallel for shared(Vettore_A, alpha) private(i,j) num_threads(num_core)
    for(i=0; i<M;i++)
    {
        for(j=0; j<M;j++)
        {
            if(i == j)
            {
                Matrice[i][j] = Vettore_A[i]*alpha;
            }else {
                Matrice[i][j] = 0;
            }
        }
    } 

    printMatrix(Matrice, M, M, "Matrice finale");

    deallocationMatrix(&Matrice, M);
    free(Vettore_A);
    return 0;
}




void allocationMatrix(int*** matrix, int N, int M) {
    *matrix = (int**) calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++)
        (*matrix)[i] = (int*) calloc(M, sizeof(int));
}

void fillMatrix(int*** matrix, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            (*matrix)[i][j] = rand() % 6+2;
}

void printMatrix(int** matrix, int N, int M, char name[]) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%d    ", matrix[i][j]);
        printf("\n");
    }
}

void deallocationMatrix(int*** matrix, int N) {
    for (int i = 0; i < N; i++)
        free((*matrix)[i]);
    free(*matrix);
}

void printVector( int* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%d ", a[i] );
    printf( "\n" );
}