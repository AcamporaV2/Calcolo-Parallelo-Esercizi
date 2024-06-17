/*

Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP. 
Il programma deve essere organizzato come segue: 

1)il core master deve generare due vettori casuali di dimensione N. 

2)Ogni core deve sommare ad ogni elemento dei due vettori il proprio
identificativo e collaborare alla costruzione di una
matrice, di dimensione N×M, con M=2np, le cui
colonne, a due a due, sono i due vettori ottenuti nella
fase precedente.

*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void allocationMatrix(int***, int, int);
void fillMatrix(int***, int, int);
void printMatrix(int**, int, int, char[]);
void deallocationMatrix(int***, int);
void printVector(int* vector, int N, char name[]);


int main()
{
    int **Matrice;
    int *Vettore_A;
    int *Vettore_B;
    int N, M;
    int np;

    srand(time(NULL));

    printf("Inserisci N:");
    scanf("%d", &N);
    
    printf("inserisci numero core:");
    scanf("%d", &np);
   

    M = 2 * np;
    printf("M è uguale a %d", M);

    Vettore_A = (int*) malloc(N * sizeof(int));
    Vettore_B = (int*) malloc(N * sizeof(int));

    #pragma omp master
    {
        for(size_t i = 0; i < N; i++)
        {
            Vettore_A[i]= rand() % 9 + 1; //da 1 a 9
            Vettore_B[i]= rand() % 9 + 1;
        }
    }

    printVector(Vettore_A, N, "Vettore_A");
    printVector(Vettore_B, N, "Vettore_B");

   // allocationMatrix(&Matrice, N, M);

   #pragma omp parallel shared(Matrice, Vettore_A, Vettore_B, N, M) num_threads(np)
    {
         // Ogni thread alloca la sua porzione di Matrice
        #pragma omp single
        {
            allocationMatrix(&Matrice, N, M);
        }

        #pragma omp for 
        for (int i = 0; i < N; i++) {

            int id = omp_get_thread_num();

            // Assegna tutti gli elementi di Vettore_A e Vettore_B alla prima colonna del thread
            for (int j = 0; j < N; j++) {
                Matrice[j][2 * id] = Vettore_A[j] + id;
            }

            for (int j = 0; j < N; j++) {  
                Matrice[j][2 * id + 1] = Vettore_B[j] + id;
            }
        }

    }

    
    printMatrix(Matrice, N, M, "Resulting Matrix");

    free(Vettore_A);
    free(Vettore_B);
    deallocationMatrix(&Matrice, N);

    return 0;
}




void printVector(int* vector, int N, char name[]) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        printf("%d\t", vector[i]);
    }
    printf("\n");
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
