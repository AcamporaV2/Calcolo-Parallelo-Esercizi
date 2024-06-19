/*Scrivere un programma parallelo per l'ambiente QUAD-CORE con pxq=2x2 core, che impieghi il linguaggio C ed utilizzi la libreria OPENMP, il programma deve essere organizzato come segue:
Il core master deve definire una matrice A di dimensione N*N=8x8 le cui entrate sono casualmente generate in un intervallo [2,7]. Quindi, ogni core deve sommare tra loro gli elementi di un blocco quadrato della matrice A di dimensione N/2*N/2=4x4, conservando i valori in un vettore B shared di dimensione N/2=4.
Infine, i core devono collaborare per calcolare la somma in finale tra gli elementi di tale vettore B. Il programma in output deve stampare la somma totale calcolata e il tempo d'esecuzione dell'algoritmo. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createMatrix(int **matrix, int righe, int colonne);
void viewMatrix(int **matrix, int righe, int colonne);
void sommaBloccoQuadrato(int **matrix, int righe, int colonne);


int main(){
    int **matrix;
    int righe = 8;
    int colonne = 8;
    

    //Definition of the matrix N = 8x8 with pseudocasual number in the intervaò [2,7]
    matrix = createMatrix(matrix,righe,colonne);
    //viewMatrix(matrix,righe,colonne);
    sommaBloccoQuadrato(matrix,colonne,righe);




}

int** createMatrix(int **matrix, int righe, int colonne){

    #pragma omp master
        {
            //printf("Questo è il thread master con ID %d\n", omp_get_thread_num());
             //Allocation of the rows
            matrix = malloc(righe * sizeof(int *));

            for(size_t i = 0;i<righe;i++){
                
            matrix[i] = malloc(colonne * sizeof(int *));
            
            }
            //Inserisco gli elementi all'interno della matrice
            for (int i = 0; i < righe; i++) {
                for (int j = 0; j < colonne; j++) {
                    // Numeri casuali tra 2 e 7
                    matrix[i][j] = 2 + rand() % 6;
                }
            }
        
   

            
        }
    printf(" \n Returno la matrice \n ");
    return matrix;

}


void viewMatrix(int **matrix, int righe, int colonne){
    for (size_t i = 0; i < righe; i++) {
        for (size_t j = 0; j < colonne; j++) {
             // Numeri casuali tra 2 e 7
            printf("[%ld][%ld]: %d \n ",i,j,matrix[i][j]);  
        }
    }
}

void sommaBloccoQuadrato(int **matrix, int righe, int colonne){
size_t l = 0;
int *vettore = malloc(sizeof(int *) * 4);
size_t i,j,b,h;
int firstEntry = 0;
int thread = 2;
#pragma omp parallel for collapse(2) shared(righe, colonne, matrix, vettore) private(i, j,b,h,l,firstEntry)
for(i = 0; i<righe;i+=4){
    for(j = 0; j<colonne; j+=4){
        //Ogni core si occupa di una riga
        int numero = omp_get_thread_num();
        firstEntry = 0;
        l = 0;
        printf("\n Numero thread = %d l = %ld first entry = %d\n ",numero,l,firstEntry);
        //Per la gestione della variabile l c'è bisogno di una gestione diversa  e piu intelligente
        
        if(numero == 0){
            if(firstEntry == 0){
                printf("Entro qui con numero == 0");
                l = 0;
                firstEntry = 1;
            }else{
                l++;
            }
        
        }else if(numero == 1){
            
            if(firstEntry == 0){
                printf("Entro qui con numero == 1");
                l = 1;
                firstEntry = 1;
            }else{
                l++;
            }
        }else if(numero == 2){
            if(firstEntry == 0){
                printf("Entro qui con numero == 1");
                l = 2;
                firstEntry = 1;
            }else{
                l++;
            }
        }else if(numero == 3){
            if(firstEntry == 0){
                printf("Entro qui con numero == 1");
                l = 3;
                firstEntry = 1;
            }else{
                l++;
            }
        }
        printf("\n \n \n Ciao io sono %d e mi occupo del Blocco %ld  e vettore[%ld] : %d \n \n \n ",numero,j,l,vettore[l]);
        for(b = i; b< i + 4; b++){
            for(h = j; h< j + 4; h++){
                
                vettore[l] += matrix[b][h];
                printf("[%ld][%ld] : %d  e vettore[%ld]: %d \n",b,h,matrix[b][h],l,vettore[l]);
            }
        }
    }
}
}