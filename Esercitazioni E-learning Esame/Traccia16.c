/*

Implementare un programma parallelo per l’ambiente multicore con nq×np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

il core master deve costruire
una matrice A, di dimensione M×N, i cui blocchi sono
generati casualmente e in parallelo da ogni core. 


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
    int i,j,M,N, np, nq;
    int num_core;
    int **Matrice;

    printf("Inserisci M:");
    scanf("%d", &M);

    
    printf("Inserisci N:");
    scanf("%d", &N);

    
    printf("Inserisci core Q:");
    scanf("%d", &nq);

    printf("Inserisci core P:");
    scanf("%d", &np);

    num_core = nq * np;
    srand(time(NULL));

    int sizeBlocco = N/nq;

    allocationMatrix(&Matrice, M, N);

    #pragma omp parallel for shared(Matrice) private(i,j) num_threads(num_core)
    for(int bloccoRiga = 0; bloccoRiga < M; bloccoRiga += sizeBlocco)
    {
        for(int bloccoColonna = 0; bloccoColonna < N; bloccoColonna +=sizeBlocco)
        {
            int thread_id = omp_get_thread_num();
            printf("Thread %d is working on block (%d, %d)\n", thread_id, bloccoRiga, bloccoColonna);
            for(i = bloccoRiga; i < bloccoRiga + sizeBlocco && i < M; i++)
            {
                for(j = bloccoColonna; j < bloccoColonna + sizeBlocco && j < N; j++)
                {
                    Matrice[i][j] = rand() % 6 +1;
                }
            }
        }
    }

    printMatrix(Matrice, M, N, "Matrice ciao");
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
