/*
traccia 2

Implementazione di un algoritmo parallelo (np core)
per il calcolo dell’operazione c=alpha*a+b, con a,b
vettori di dimensione N e alpha uno scalare, in
ambiente openMP 

*/

//è chatgpt ma puoiu vedere somma vettori e credo copiare quello aggiungdo ciò che sevre

#include <omp.h>
#include <stdio.h>

void vector_operation(double *c, double alpha, double *a, double *b, int N) {
    // Parallelize the vector operation c = alpha * a + b using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        c[i] = alpha * (a[i] + b[i]);
    }
}

int main() {
    int N = 5;  // dimensione dei vettori
    double alpha;
    double a[N], b[N], c[N];

    printf("Inserisci alpha");
    scanf("%lf",&alpha);

    printf("hai inserito %f", alpha);

    // Inizializzazione dei vettori a e b (esempio)
    for (int i = 0; i < N; ++i) {
        a[i] = i + 1;
        b[i] = 2 * (i + 1);
    }


    printf("Vettore a:\n");
    for (int i = 0; i < N; ++i) {
        printf("%f\n", a[i]);
    }

    printf("Vettore b:\n");
    for (int i = 0; i < N; ++i) {
        printf("%f\n", b[i]);
    }

    // Calcolo parallelo di c = alpha * a + b
    vector_operation(c, alpha, a, b, N);

    // Stampare il risultato (esempio)
    printf("Risultato:\n");
    for (int i = 0; i < N; ++i) {
        printf("%f\n", c[i]);
    }

    return 0;
}
