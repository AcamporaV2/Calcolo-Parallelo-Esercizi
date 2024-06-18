/*
Implementazione di un algoritmo parallelo (np core)
per il calcolo dell'operazione c=a+b con a,b vettori di dimensione N
ovviamente, in ambiente openMP
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main(){
    
    int N;//size degli array
    double *a,*b,*c;//array
    int th;//numero threads
    int i;//indice 
    double t0,t1;//variabili per il calcolo del tempo impiegato

    printf("Inserisci il valore di N\n");
        scanf("%d",&N);//inserimento del size degli array

        printf("Inserisci numero di threads da utilizzare\n");
        scanf("%d",&th);//inserimento del numero di threads

        //Allocazione dinamica degli array
        a=(double *)calloc(N,sizeof(double));
        b=(double *)calloc(N,sizeof(double));
        c=(double *)calloc(N,sizeof(double));



    //riempimento dei vettori a e b
    srand(time(NULL));
    for(i=0;i<N;i++)
    {

        a[i]=rand()%10+1;
        b[i]=rand()%10+1;

    }

    t0=omp_get_wtime();
    //inizio della direttiva parallela
    #pragma omp parallel for private(i) shared(a,b,c) num_threads(th)
    for(i=0;i<N;i++)
    {
         c[i]=a[i]+b[i];//somma tra vettori
    }

    t1=omp_get_wtime();

    printf("Il vettore risultante c è:\n");

    for(i=0;i<N;i++)
    {
        printf("c[%d]=%f\n",i,c[i]);//stampa del vettore somma
    }

    printf("Il tempo impiegato dall'algoritmo è : %f",t1-t0);
    //deallocazione dinamica della memoria
    free(a);
    free(b);
    free(c);

    return 0;
}

