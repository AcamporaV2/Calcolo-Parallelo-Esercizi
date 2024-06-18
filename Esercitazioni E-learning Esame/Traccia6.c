/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve leggere una matrice A di dimensione N×N ed uno scalare alpha.

2)Quindi, i core devono collaborare per calcolare il  prodotto tra lo scalare alpha e la matrice A, sfruttano una strategia di parallelizzazione che usi la 
distribuzione per colonne della matrice A come decomposizione del dominio. 


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
    int N, np, alpha, i,j;
    srand(time(NULL));
    printf("Inserisci numero N per righe e colonne:");
    scanf("%d", &N);

    printf("inserisci numero core");
    scanf("%d", &np);

    //punto1
    #pragma omp master
    {
        printf("Inserisci lo scalare");
        scanf("%d", &alpha);

        printf("Alpha: %d", alpha);
        allocationMatrix(&Matrice, N, N);
        fillMatrix(&Matrice, N, N);
        printMatrix(Matrice, N,N, "matrice");
    }

    #pragma omp parallel for shared(Matrice, alpha) private (i,j) num_threads(np)
    for(j = 0; j < N; j++)
    {
        for (i = 0; i< N; i++)
        {
            Matrice[i][j] *= alpha;
        }
    }

    printMatrix(Matrice, N, N, "Matrice B = alpha * Matrice A");

    deallocationMatrix(&Matrice, N);

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
