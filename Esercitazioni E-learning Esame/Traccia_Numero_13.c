/*

Implementare un programma parallelo perl’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master generare unamatrice A di dimensione M×M. 

2)Quindi, i core devo collaborare valutare il minimo valore tra gli elementi di A e successivamente costruire la matrice B i cui
elementi sono dati dalla somma di tale valore minimo per gli elementi di posto corrispondente della matrice di partenza.


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
    int **Matrice_A, **Matrice_B;
    int *Vettore;
    int N; //righe e colonne matrice
    int Num_core; // numero core
    int i, j; 
    int minimo;
    
    //double tempo_inizio, tempo_fine;

    srand(time(NULL));
    printf("Inserisci numero righe N:");
    scanf("%d", &N);

   

    printf("Inserisci numero di core:");
    scanf("%d", &Num_core);

   
    //punto 1
    #pragma omp master
    {
        allocationMatrix(&Matrice_A, N, N);
        fillMatrix(&Matrice_A, N, N);
        printMatrix(Matrice_A, N, N, "Matrice iniziale:");
        allocationMatrix(&Matrice_B, N, N);
    }
    minimo = Matrice_A[0][0];

    #pragma omp parallel for reduction(min:minimo) shared(Matrice_A) private(i,j) num_threads(Num_core)
    for(i=0; i<N;i++)
    {
        for(j = 0; j < N; j++)
        {
            if(Matrice_A[i][j] < minimo)
            {
                minimo = Matrice_A[i][j];
            }
        }
    }

    printf("Minimo = %d\n", minimo);

    #pragma omp parallel for shared(Matrice_A, Matrice_B) private(i,j) num_threads(Num_core)
    for(i = 0; i < N; i++)
    {
        for( j = 0; j<N;j++)
        {
            Matrice_B[i][j] = minimo + Matrice_A[i][j];
        }
    }


    printMatrix(Matrice_B, N, N, "Matrice B");

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
