/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti che impieghi la libreria OpenMP
Il programma deve essere organizzato come segue:
1)Il core master deve generare una matrice di dimensione NxM.
2)Ogni core deve estrarre la riga della matrice con indice uguale al proprio identificativo e conservarla in un vettore locale.
3)Successivamente ogni core deve sommare gli elementi di tale vettore e conservare il risultato il un vettore c di dimensione np.
4)I core devono collaborare per individuare il massimo tra gli elementi del vettore c.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int N, M, nthreads, i, j;
    double **A;
    double *c;
    double *local;
    int id;
    double max=0.0;

    printf("Inserire le dimensioni della matrice: N-M\n");
    scanf("%d %d", &N, &M);

    printf("Inserire il numero di threads:\n");
    scanf("%d", &nthreads);

    // Allocazione della matrice A
    A = (double **)calloc(N, sizeof(double*));
    for (i = 0; i < N; i++) {
        A[i] = (double*)calloc(M, sizeof(double));
    }

    // Allocazione del vettore c
    c = (double *)calloc(nthreads, sizeof(double));

    // Inizializzazione della matrice con valori casuali
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            A[i][j] = rand() % 10 + 1;
        }
    }

    // Stampa della matrice A
    printf("La matrice A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    // Sezione parallela
    #pragma omp parallel private(local, i, j, id) shared(A, c) num_threads(nthreads)
    {
        id = omp_get_thread_num();
        if (id < N) 
        {
            // Allocazione del vettore locale per ogni thread
            local = (double *)calloc(M, sizeof(double));
            double sum = 0.0;

            // Copia della riga con indice uguale al proprio identificativo
            for (j = 0; j < M; j++) 
            {
                local[j] = A[id][j];
                sum += local[j];
            }

            // Salva la somma degli elementi del vettore locale in c[id]
            c[id] = sum;

            // Stampa del vettore locale
            printf("Thread %d, local: ", id);
            for (j = 0; j < M; j++) 
            {
                printf("%lf ", local[j]);
            }
            printf("\n");

            // Stampa della somma
            printf("Thread %d, sum: %lf\n", id, sum);

            // Deallocazione del vettore locale
            free(local);
        }
    }

    // Stampa del vettore c
    printf("Il vettore c:\n");
    for (i = 0; i < nthreads; i++) 
    {
        printf("%lf ", c[i]);
    }
    printf("\n");

	max=c[0];

    #pragma omp parallel for private(i) shared(c) num_threads(nthreads) reduction(max:max)
    for(i=0;i<nthreads;i++)
    {

        if(c[i]>max)
        {
        max=c[i];
        }
    }
    printf("Il max è:%lf\n",max);

    // Deallocazione della matrice A
    for (i = 0; i < N; i++) 
    {
        free(A[i]);
    }
    free(A);

    // Deallocazione del vettore c
    free(c);

    return 0;
}

