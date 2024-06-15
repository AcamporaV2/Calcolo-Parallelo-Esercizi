/*
Implementare un programma parallelo per l’ambiente multicore con np unità processanti che impieghi la libreria OpenMP.

Il programma deve essere organizzato come segue: 

1)il core master generare una matrice di dimensione N×M. 

2)Quindi, ogni core deve estrarre la riga della matrice con indice uguale al proprio identificativo e conservarla in un vettore locale;

3)successivamente deve sommare gli elementi di tale vettore e conservare il risultato in un vettore c di dimensione np. 

4)Infine, i core devo collaborare per individuare in massimo tra gli elementi del vettore c. */
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
    int N, M; //righe e colonne matrice
    int Num_core; // numero core
    int i, j; 
    
    double tempo_inizio, tempo_fine;


    srand(time(NULL));

    printf("Inserisci numero righe N:");
    scanf("%d", &N);

    printf("Inserisci numero colonne M:");
    scanf("%d", &M);

    printf("Inserisci numero di core:");
    scanf("%d", &Num_core);

    tempo_inizio = omp_get_wtime();
    //punto 1
    #pragma omp master
    {
        allocationMatrix(&Matrice, N, M);
        fillMatrix(&Matrice, N, M);
        printMatrix(Matrice, N, M, "Matrice iniziale:");
    }

    Vettore = (int*) malloc(Num_core * sizeof(int*));


    //punto 2 e 3 uniti
    #pragma omp parallel for shared(Matrice,Vettore) private (j) num_threads(Num_core)
    for (int id_thread = 0; id_thread < Num_core; id_thread++)
    {
        if (id_thread < N)
        {
            int somma_elementi = 0;
            for (j = 0; j < M; j++)
            {
                somma_elementi += Matrice[id_thread][j];
            }
            Vettore[id_thread] = somma_elementi;
        }
        else
        {
            Vettore[id_thread] = 0; // Se id
        }
    }

    // Stampa del vettore c
    printf("\nVettore c:\n");
    for (int i = 0; i < Num_core; i++) 
    {
        printf("%d ", Vettore[i]);
    }
    printf("\n");

    int max_valore = Vettore[0];
    #pragma omp parallelfor shared(Vettore) private (i)  reduction(max:max_valore) 
    {
        for (int i = 1; i < Num_core; i++) 
        {

            if (Vettore[i] > max_valore) 
            {
                max_valore = Vettore[i];
            }
        }
    }
    tempo_fine = omp_get_wtime();

    printf("\n Tempo di esecuzione: %f", tempo_fine - tempo_inizio);
    printf("\nValore massimo nel vettore c: %d\n", max_valore);

    // Deallocazione memoria
    free(Vettore);
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
