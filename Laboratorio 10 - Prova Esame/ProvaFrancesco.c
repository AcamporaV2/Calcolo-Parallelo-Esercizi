/* 

Implementare un programma parallelo per l'ambiente multicore con 

np unità processanti che impieghi la libreria Openmp. 

Il programma deve essere organizzato come segue: 

-1)Il core master deve generare una matrice B di dimensione NxN e due  

vettori a e b di lunghezza N. 

-2)I core devono collaborare per costruire in parallelo, una matrice A 

ottenuta sommando alla diagonale principale della matrice B e il vettore b 

-3)Quindi, i core devono collaborare per calcolare in parallelo il prodotto 

tra la nuova matrice A ed il vettore a, distribuendo il lavoro per colonne 

-4)Infine, il core master stampa il risultato finale ed il tempo di esecuzione. 

*/ 

//PROVA NON MIA L'HO MESSA COMUNQUE PERCHE' POTREBBE SERVIRE 

//Soluzione: 
 

#include <omp.h> 

#include <stdio.h> 

#include <stdlib.h> 

#include <math.h> 

#include <time.h> 


int main(){ 

int N,i,j;//size della matrice e indici iteratori 

double *B,*A; //matrici 

double *a,*b; //vettori 

int nthreads; //numero di threads 

double t0,t1;//variabili per misurare il tempo di esecuzione 

 

double *c; //vettore risultante 


/* Sintassi da seguire per l'inserimento delle variabili da riga di comando 

if(argc>1){  

N=atoi(argv[1]);//primo elemento linea di comando 

nthreads=atoi(argv[2]); 

} 

else{ 

printf("Errore usage : . / exec <nThreads> <M> <N> <alpha> <beta >\n"); 

exit(EXIT_FAILURE);  

} 

*/ 

 

//Punto 1 

printf("Inserisci N :\n"); 

scanf("%d",&N); //inserimento da tastiera del size 

 

printf("Inserisci Num threads :\n"); 

scanf("%d",&nthreads); //inserimento da tastiera del numero di threads 

 

 

//Allocazione dinamica della matrice B/ 

B=(double **)malloc(N*sizeof(double)); 

for(i=0;i<N;i++){ 

B[i]=(double *)malloc(N*sizeof(double)); 

} 

 

//Allocazione dinamica della matrice B/ 

A=(double **)malloc(N*sizeof(double)); 

for(i=0;i<N;i++){ 

A[i]=(double *)malloc(N*sizeof(double)); 

} 

//Allocazione dei due vettori 

a=(double *)malloc(N*sizeof(double)); 

b=(double *)malloc(N*sizeof(double)); 

c=(double *)calloc(N,sizeof(double)); //allocazione dinamica del vettore c 

//Inserimento valori Matrice e vettori 

printf("Inserimento valori Matrice\n"); 

for(i=0;i<N;i++){ 

for(j=0;j<N;j++){ 

B[i][j]=1; //tutti 1 

} 

} 

/* 

nb: per effettuare delle prove (in sede d'esame) è sempre meglio 

riempire la matrice con valori che sono facili da verificare  

su carta e penna, una volta verificata la correttezza dell'algoritmo 

si può procedere con il riempimento con valori casuali 

*/ 

/* 

srand(time(NULL)); 

for (int i = 0; i < rows; i++) { 

for (int j = 0; j < columns; j++) { 

B[i][j] = rand() % 10 + 1; 

} 

} 

*/ 

 

 

//Copia degli elementi della matrice B in A 

for(i=0;i<N;i++){ 

for(j=0;j<N;j++){ 

A[i][j]=B[i][j]; 

} 

} 

 

//Stampa degli elementi della matrice 

printf("L matrice ha i seguenti valori\n"); 

for(i=0;i<N;i++){ 

for(j=0;j<N;j++){ 

printf(" B[%d][%d]=%f;\n", i, j, B[i][j]); 

} 

} 

//Riempimento dei vettori 

for(i=0;i<N;i++){ 

a[i]=2; //vettore A tutti 2 

b[i]=3; //vettore B tutti 3 

} 

/* 

nb: per effettuare delle prove (in sede d'esame) è sempre meglio 

riempire i vettori con valori che sono facili da verificare  

su carta e penna, una volta verificata la correttezza dell'algoritmo 

si può procedere con il riempimento con valori casuali 

*/ 

/* 

srand(time(NULL)); 

for (int i = 0; i < n; i++){ 

array[i] = rand() % 5 + 1; 

} 

*/ 

 

 

//Stampa a video dei vettori 

printf("Il vettore a è:\n"); 

for(i=0;i<N;i++){ 

printf("a[%d]=%f\n",i,a[i]); 

} 

 

printf("Il vettore b è:\n"); 

for(i=0;i<N;i++){ 

printf("b[%d]=%f\n",i,b[i]); 

} 

 

//Inizio del costrutto parallelo 

t0=omp_get_wtime(); 

#pragma omp parallel for shared(A,B,b) private(i) num_threads(nthreads) 

for(i=0;i<N;i++){ 

A[i][i]+=b[i]; //andiamo ad effettuare il punto 2) 

} 

//stampa a video della nuova matrice 

printf("La nuova matrice A è:\n"); 

for(i=0;i<N;i++){ 

for(j=0;j<N;j++){ 

printf("A[%d][%d]=%f\n", i, j, A[i][j]); 

} 

} 

//Punto 3 

#pragma omp parallel for shared(A,c,a) private(i,j) num_threads(nthreads) //direttiva parallela 

for(j=0;j<N;j++){  

for(i=0;i<N;i++){  

#pragma omp atomic 

c[i]+=A[i][j]*a[j]; //calcolo del vettore risultante 

//la componente i-esima del vettore risultante è data dal prodotto scalare tra la riga i-esima della matrice e il j-esimo elemento del vettore x 

} 

} 

t1=omp_get_wtime(); 

//Punto 4 

printf("Il vettore risultante è :\n"); //Stampa del risultato 

for(i=0;i<N;i++){ 

printf("C[%d]=%f\n",i,c[i]); 

} 

printf("Il tempo impiegato è %lf\n",t1-t0); 

 

//Deallocazione della memoria 

free(b); 

free(c); 

free(a); 

for(i=0;i<N;i++){ 

free(A[i]); 

} 

for(i=0;i<N;i++){ 

free(B[i]); 

} 

free(A); 

free(B); 
}
