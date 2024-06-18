/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve leggere una matrice di dimensione N×M, 

2)quindi i core devo collaborare per sommare in parallelo i vettori corrispondenti alle righe dispari della matrice. 



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

    Vettore = (int*) calloc(M, sizeof(int));

    #pragma omp parallel for shared(Matrice,Vettore) private(i,j) num_threads(num_core)
    for(i=0; i< N; i++)
    {
        int somma = 0;
        for(j=0; j < M; j++)
        {
            if(i%2!=0)
            {
                somma += Matrice[i][j];
            }
            
        }
       Vettore[i]= somma;
    }

    printf("Il vettore risultante r è:\n");

	for(i=0;i<M;i++)
	{
		printf("Vettore[%d]=%d\n",i,Vettore[i]);
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

