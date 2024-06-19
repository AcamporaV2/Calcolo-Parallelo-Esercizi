/* Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master generare una
matrice di dimensione N×M. Quindi, ogni core deve
estrarre la riga della matrice con indice uguale al
proprio identificativo e conservarla in un vettore locale;
successivamente deve sommare gli elementi di tale
vettore e conservare il risultato in un vettore c di
dimensione np. Infine, i core devono collaborare per
individuare in massimo tra gli elementi del vettore c. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void riempiMatrice(double **matrix, int n, int m);
void stampaMatrice(double **matrix, int n, int m);
double** allocaMatrice(int n, int m);
void deallocaMatrice(double **matrix, int n);

int main() {
    int n, m, np;
    printf("Inserisci il numero di righe: \n");
    scanf("%d", &n);
    printf("Inserisci il numero di colonne: \n");
    scanf("%d", &m);

    np = omp_get_max_threads();
    printf("Numero di core disponibili: %d\n", np);

    // allochiamo dinamicamente la matrice
    double **matrix = allocaMatrice(n, m);

    // inizializziamo la matrice
    srand(time(NULL));
    riempiMatrice(matrix, n, m);

    // stampa della matrice
    printf("Matrice generata:\n");
    stampaMatrice(matrix, n, m);

    // vettore c con i risultati locali
    double *c = (double *)malloc(n * sizeof(double));

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        if (thread_id < n) {
            double somma = 0.0;
            // il core estrae la riga e calcola la somma
            for (int j = 0; j < m; j++) {
                somma += matrix[thread_id][j];
            }
            // conserviamo il risultato nel vettore c
            c[thread_id] = somma;
        }
    }

    // stampiamo il vettore c
    printf("Vettore somme righe: \n");
    for (int i = 0; i < n; i++) {
        printf("%3.1lf ", c[i]);
    }
    printf("\n");

    // max elemento nel vettore c
    double max_val = c[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < n; i++) {
        if (c[i] > max_val) {
            max_val = c[i];
        }
    }

    // stampa val max
    printf("Il massimo valore nel vettore c è: %3.1lf\n", max_val);

    deallocaMatrice(matrix, n);
    free(c);

    return 0;
}

void riempiMatrice(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX * 9; // Genera numero casuale tra 0 e 9
        }
    }
}

void stampaMatrice(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3.1lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

double** allocaMatrice(int n, int m) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }
    return matrix;
}

void deallocaMatrice(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}