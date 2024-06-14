
/*
Scrivere un programma parallelo per l'ambiente QUAD-CORE con pxq=2x2 core, che impieghi il linguaggio C ed utilizzi la libreria OPENMP, il programma deve essere organizzato come segue:

1)Il core master deve definire una matrice A di dimensione N*N=8x8 le cui entrate sono casualmente generate in un intervallo [2,7].

2)Quindi, ogni core deve sommare tra loro gli elementi di un blocco quadrato della matrice A di dimensione N/2*N/2=4x4, conservando i valori in un vettore B shared di dimensione N/2=4.

3)Infine, i core devono collaborare per calcolare la somma in finale tra gli elementi di tale vettore B. 

4)Il programma in output deve stampare la somma totale calcolata e il tempo d'esecuzione dell'algoritmo. */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

void allocationMatrix(int***, int, int);
void fillMatrix(int***, int, int);
void printMatrix(int**, int, int, char[]);
void deallocationMatrix(int***, int);

int main() {
    int **Matrice;
    int *Vettore;
    int riga = 8;
    int colonne = 8;
    int numero_core = 4;
    size_t i, j;
    double tempo_inizio, tempo_fine;

    srand(time(NULL));

    tempo_inizio = omp_get_wtime();

    Vettore = (int*) malloc((riga / 2) * sizeof(int));

    // Parte 1: matrice 8x8 in un intervallo [2,7]
    #pragma omp master
    {
        allocationMatrix(&Matrice, riga, colonne);
        fillMatrix(&Matrice, riga, colonne);
        printMatrix(Matrice, riga, colonne, "Matrice Iniziale");
    }

    // Parte 2: somma di n/2 = 4 blocchi matrici
    #pragma omp parallel shared(Matrice, Vettore) private(i, j) num_threads(numero_core)
    {
        int thread_id = omp_get_thread_num();
        int block_size = riga / 2;

        // Ogni thread somma gli elementi di uno dei quattro blocchi
        int sum = 0;
        int row_start = (thread_id / 2) * block_size;
        int col_start = (thread_id % 2) * block_size;

        for (i = row_start; i < row_start + block_size; i++) {

            for (j = col_start; j < col_start + block_size; j++) {

                sum += Matrice[i][j];

            }
        }
        // Salvare il risultato nel vettore condiviso
        Vettore[thread_id] = sum;
    }
    /*
        thread_id = 0: row_start = 0, col_start = 0 (primo blocco in alto a sinistra)
        thread_id = 1: row_start = 0, col_start = 4 (secondo blocco in alto a destra)
        thread_id = 2: row_start = 4, col_start = 0 (terzo blocco in basso a sinistra)
        thread_id = 3: row_start = 4, col_start = 4 (quarto blocco in basso a destra)
    */


    // Parte 3: Calcolo della somma finale degli elementi del vettore B
    int somma_finale = 0;
    #pragma omp parallel for reduction(+:somma_finale) num_threads(numero_core)
    for (i = 0; i < numero_core; i++) {
        somma_finale += Vettore[i];
    }



    // Stampa dei risultati
    #pragma omp master
    {
        for (i = 0; i < riga / 2; i++) {
            printf("Somma del blocco %zu: %d\n", i, Vettore[i]);
        }

        printf("Somma finale: %d\n", somma_finale);

        // Tempo di fine
        tempo_fine = omp_get_wtime();
        // Il master thread deve stampare il tempo di esecuzione
        printf("\nTempo di esecuzione: %lf\n", tempo_fine - tempo_inizio);

        // Deallocazione della matrice
        deallocationMatrix(&Matrice, riga);
    }

    free(Vettore);

    return 0;
}





//FUNZIONI



void allocationMatrix(int*** matrix, int N, int M) {
    *matrix = (int**) calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++)
        (*matrix)[i] = (int*) calloc(M, sizeof(int));
}

void fillMatrix(int*** matrix, int N, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            (*matrix)[i][j] = rand() % 6 + 2;
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
