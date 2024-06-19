/*
L'esercizio prende in input dal'utente il numero di righe e colonne per una matrice. 
Quindi, genera casualmente valori per riempire la matrice e calcola la sua trasposta.
 Successivamente, estrae la diagonale dalla matrice trasposta e calcola la somma e il prodotto 
 degli elementi della diagonale. Infine, stampa gli elementi della diagonale, la somma e il prodotto. 
*/



#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void riempiLaMatrice(int ** matrix, int row, int col);
void mostraLaMatrice(int ** matrix, int row, int col);
void calcolaLaTrasposta(int **matrix,int **trasposta, int row, int col);
void sommaProdottoDiagonale(int **trasposta,int righe,int colonne,int *somma,int *prodotto,int vettore[]);



int main(){

int scalare = 0;
//int **matrice;
int righe;
int colonne;
int somma = 0;
int prodotto = 0;





//Inserimento scalare
printf("Inserisci uno scalare \n");
scanf("%d", &scalare);
printf("Hai inserito %d \n", scalare);

//Chiedo il numero di righe e di colonne
printf("Inserisci il numero di righe \n");
scanf("%d", &righe);
printf("Inserisci il numero di colonne \n");
scanf("%d", &colonne);

//Allocazione della matrice
int **matrice = malloc(righe * sizeof(int *));
int **trasposta = malloc(righe * sizeof(int *));
int *vettore =malloc(righe* sizeof(int *));


for(size_t i = 0;i<righe;i++){
    matrice[i] = malloc(colonne * sizeof(int *));
    trasposta[i] = malloc(colonne * sizeof(int *));

}



riempiLaMatrice(matrice,righe,colonne);
mostraLaMatrice(matrice,righe,colonne);
calcolaLaTrasposta(matrice,trasposta,righe,colonne);
printf("Mostro la matrice trasposta  -----> \n");
mostraLaMatrice(trasposta,righe,colonne);

//Moltiplicazione matrice x scalare
size_t i,j;
#pragma omp parallel for shared(righe, colonne, matrice, scalare) private(i, j)
sommaProdottoDiagonale(trasposta,righe,colonne,&somma,&prodotto,vettore);
printf("Somma ----> %d ", somma);



//mostraLaMatrice(matrice,righe,colonne);
return 0;
}


void riempiLaMatrice(int **matrice, int colonne, int righe){
    for(size_t i = 0; i<righe; i++){
        
        for(size_t j = 0; j<colonne; j++){
            matrice[i][j] = (i) * 2;
            //printf("[%ld][%ld] = %d", i,j,matrice[i][j]);
        }
    }

}


void mostraLaMatrice(int **matrice, int colonne, int righe){
    for(size_t i = 0; i<righe; i++){
        
        for(size_t j = 0; j<colonne; j++){
            printf("[%ld][%ld] = %d \n ", i,j,matrice[i][j]);
        }
    }

printf("\n  Fine della matrice  \n");

}


//Serve a calcolare la trasposta di una matrice
void calcolaLaTrasposta(int **matrice,int **trasposta,int righe, int colonne){
   for(size_t i = 0; i<righe; i++){
        
        for(size_t j = 0; j<colonne; j++){
            trasposta[j][i] = matrice[i][j];
            //printf("[%ld][%ld] = %d \n ", i,j,matrice[i][j]);
        }
    }
}

void sommaProdottoDiagonale(int **trasposta,int righe, int colonne, int *somma, int *prodotto,int *vettore){
    for(int i = 0; i < righe; i++){
        vettore[i] = trasposta[i][i];
        //Sommo gli elementi della diagonale
        *somma += vettore[i];
        //Prodotto degli elementi della diagonale
        *prodotto *=  vettore[i];
        printf(" \n \n \n Stampo %d  %d   %d  \n \n \n", *somma,*prodotto,vettore[i]);

    }

    printf("Somma    ------> %d \n", *somma);
    printf("Prodotto ------> %d \n", *prodotto);
    

}





