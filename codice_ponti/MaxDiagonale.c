/*


Assegnata una matrice di dimensione N×N, estrarre in parallelo gli elementi
della diagonale principale e ricopiarli in un vettore, quindi calcolarne il
massimo, con una procedura parallela


*/

//Praticamente copiato perchè non mi riusciva 

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define MAXVALUE 100 //Valore massimo nel fill

void alloc_matrix(int *** matrix, int row, int col);
void fill_matrix(int ** matrix, int row, int col, int max_element);
void print_matrix(int ** matrix, int row, int col);
void dealloc_matrix(int ** matrix, int row);

int main()
{
    int N, massimoDiag, x;
    int** matrice;
    int* vettore;

    srand(time(NULL));

    printf("\nInserisci N:");
    scanf("%d", &N);
    //printf("\nN: %d", N);

    alloc_matrix(&matrice, N, N);
    fill_matrix(matrice, N, N, MAXVALUE);
    print_matrix(matrice, N, N);

    massimoDiag = INT_MIN; 

    #pragma omp parallel shared(matrice, N) private(x)
    {
        #pragma omp for reduction(max:massimoDiag)
        for( size_t i = 0; i < N; i++)
        {
            x = matrice[i][i];

            if(massimoDiag < x)
            {
                massimoDiag = x;
            }
        }

        //Barriera che forza i thread ad attendere il completamento di tutte le istruzioni precedenti da parte di tutti gli altri
        #pragma omp barrier 

        //Solo il master thread farà ciò
        #pragma omp master
        {
            printf("il massimo è: %d", massimoDiag);
        }

    }

    dealloc_matrix(matrice, N);


    return 0;
}



void alloc_matrix(int *** matrix, int row, int col) {
    *matrix = malloc(row * sizeof(int *));
    #pragma omp parallel for shared(matrix, row, col)
    for (size_t i = 0; i < row; ++i) {
        (*matrix)[i] = malloc(col * sizeof(int));
    }
}

void fill_matrix(int ** matrix, int row, int col, int max_element) {
    #pragma omp parallel for shared(matrix, row, col)
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            matrix[i][j] = rand() % max_element;
        }
    }
}

void print_matrix(int ** matrix, int row, int col) {
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void dealloc_matrix(int ** matrix, int row) {
    #pragma omp parallel for shared(matrix, row)
    for (size_t i = 0; i < row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
