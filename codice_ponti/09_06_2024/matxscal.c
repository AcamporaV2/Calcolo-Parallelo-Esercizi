/*
L'utente inserisce un valore chiamato scalar che rappresenta lo scalare. 
Questo valore viene quindi moltiplicato per ogni elemento della matrice generato casualmente.
 Quindi, ogni elemento della matrice viene moltiplicato per lo stesso scalare,
  ottenendo una matrice in cui ogni valore è stato scalato rispetto al valore originale.
   Ad esempio, se l'utente inserisce uno scalare di 2,
 ogni elemento della matrice verrà moltiplicato per 2, raddoppiando il valore di ogni elemento.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void riempiMatrice(double **matrix, int n, int m);
void stampaMatrice(double **matrix, int n, int m);

int main() {
    double scalar;
    int n, m;

    printf("Inserisci scalare: \n");
    scanf("%lf", &scalar);
    printf("Inserisci righe: \n");
    scanf("%d", &n);
    printf("Inserisci colonne: \n");
    scanf("%d", &m);

    srand(time(NULL));

    // Alloca dinamicamente la matrice
    double **a = (double **)malloc(n * sizeof(double *));
    for(int i = 0; i < n; i++) {
        a[i] = (double *)malloc(m * sizeof(double));
    }

    // Inizializza la matrice
    riempiMatrice(a, n, m);

    // Stampa della matrice prima della moltiplicazione
    printf("Matrice prima della moltiplicazione:\n");
    stampaMatrice(a, n, m);

    // Moltiplicazione della matrice per lo scalare in parallelo
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            a[i][j] *= scalar;
        }
    }

    // Stampa della matrice dopo la moltiplicazione
    printf("Matrice dopo la moltiplicazione:\n");
    stampaMatrice(a, n, m);

    // Dealloca la matrice
    for(int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);

    return 0;
}

void riempiMatrice(double **matrix, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX * 9; // Genera numero casuale tra 0 e 9
        }
    }
}

void stampaMatrice(double **matrix, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%3.1lf ", matrix[i][j]);
        }
        printf("\n");
    }
}