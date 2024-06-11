#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


//Prodotto matrice per scalare usando la prima strategia
//Non farò le altre wallahi 
//Se decidi di mettere i, j, e matrice all'inizio di tutto per qualche motivo non va il programma oltre lo scanf delle colonne.

void stampaMatrice(int ** matrix, int row, int col);

int main(){
    srand(time(NULL));
    int righe, colonne;

    printf("inserisci numero righe:");
    scanf("%d",&righe);

    printf("inserisci numero colonne: ");
    scanf("%d", &colonne);

    int ** matrice = malloc( righe * sizeof(int*));

    for (size_t i = 0; i< righe; ++i)
    {
        matrice[i] = malloc(colonne * sizeof(int));
    }

    //Allocamento matrice
    for (size_t i = 0; i < righe; ++i) {
        for (size_t j = 0; j < colonne; ++j) {

            matrice[i][j] = rand() % 20;
        }
    }
    int scalare;

    printf("inserisci scalare:");
    scanf("%d", &scalare);

    printf("Prima Matrice:");
    stampaMatrice(matrice, righe, colonne);


    size_t i, j;

    #pragma omp parallel for shared(righe, colonne, matrice, scalare) private(i, j)
    for (i = 0; i < righe; ++i)
    {
        for(j = 0; j < colonne; ++j)
        {
           matrice[i][j] = matrice[i][j] * scalare;
        }
    }
    

    printf("Matrice dopo:");
    stampaMatrice(matrice, righe,colonne);

    return 0;



}





void stampaMatrice(int ** matrix, int row, int col) {
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}
