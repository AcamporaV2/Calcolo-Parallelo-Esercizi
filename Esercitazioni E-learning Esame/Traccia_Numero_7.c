/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve generare
una matrice A di dimensione N×M. 

2)Quindi, i core devono collaborare per calcolare il minimo tra gli elementi delle colonne di propria competenza e
conservare tale valore in un vettore c di dimensione M. 


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
    int N, M;
    int i,j;
    int *Vettore;
    int num_core;

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


    Vettore= (int*)calloc(M, sizeof(int));

    #pragma omp parallel for shared(Matrice, Vettore) private(i,j) num_threads(num_core)
    for(j = 0; j < M; j++)
    {
        int min = Matrice[0][j];
        for(i = 0; i < N; i++)
        {
            if (Matrice[i][j] < min)
            {
                min = Matrice[i][j];
            }
        }
        Vettore[j] = min;
    }

    printf("Vettore minimi");
    for(i = 0; i < M; i++)
    {
        printf("Vettore[%d] = %d \n", i, Vettore[i]);
    }

    

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

