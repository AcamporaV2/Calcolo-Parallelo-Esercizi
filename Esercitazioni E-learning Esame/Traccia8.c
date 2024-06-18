/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve generare una matrice A di dimensione N×M. 

2)Quindi, ogni core deve estrarre N/p colonne ed effettuare localmente la somma degli elementi delle sottomatrici estratte,
conservando il risultato in un vettore b di dimensione M


*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void allocationMatrix(int***, int, int);
void fillMatrix(int***, int, int);
void printMatrix(int**, int, int, char[]);
void deallocationMatrix(int***, int);

int main()
{
    int **Matrice;
    int *Vettore;
    int N, M;
    int num_core;
    int i,j;

    srand(time(NULL));
    printf("Inserisci numero N per righe :");
    scanf("%d", &N);

    printf("Inserisci numero M  colonne:");
    scanf("%d", &M);

    printf("inserisci numero core");
    scanf("%d", &num_core);
    
    #pragma omp master
    {
        allocationMatrix(&Matrice, N, M);
        fillMatrix(&Matrice, N, M);
        printMatrix(Matrice, N, M, "Matrice iniziale");
    }


    Vettore = (int *)calloc(M, sizeof(int));

    #pragma omp parallel for shared(Matrice, Vettore) private (i,j) num_threads(num_core)
    for(j=0;j<M;j++)
    {
        int sum = 0;
        int id = omp_get_thread_num();
        for(i=0; i < N; i++)
        {   
            sum += Matrice [i][j];
            printf("Sono core %d \n", id); //Gigi se mai leggerai questo ti odio 
        }

        Vettore[j] = sum;
    }

    printf("\nVettore risultato:\n");
    for (i = 0; i < M; i++) {
        printf("%d ", Vettore[i]);
    }
    printf("\n");

    deallocationMatrix(&Matrice, N);
    free(Vettore);

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
            (*matrix)[i][j] = rand() % 6;
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

