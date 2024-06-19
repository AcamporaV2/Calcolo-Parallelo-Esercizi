/* Implementare un programma parallelo per
l’ambiente multicore con np×np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×N. Quindi, ogni core
deve sommare tra loro gli elementi di un blocco
quadrato della matrice A di dimensione (N/np)×(N/np),
conservando i valori in un vettore b. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int** createMatrix(int **matrix, int righe, int colonne);
void viewMatrix(int **matrix, int righe, int colonne);


int main(){
    int **matrix;
    int righe = 8;
    int colonne = 8;
    

    //Definition of the matrix N = 8x8 with pseudocasual number in the intervaò [2,7]
    matrix = createMatrix(matrix,righe,colonne);
    viewMatrix(matrix,righe,colonne);

    //Ogni core deve estratte N/np righe
    size_t i,j,b,h,z;
    int *vettore;
    #pragma omp parallel  shared(righe, colonne, matrix) private(i,j,b,vettore,h,z)
    {
        vettore = malloc(colonne * sizeof(int *));
        //Popolo il vettore
        for(b = 0;b<colonne;b++){
            vettore[b] = 0;
            //printf("Il mio vettore[%ld] è uguale a %d \n", b,vettore[b]);
        }
        int numberOfThreads = omp_get_num_threads()-1;
        int numberOfRow = righe/numberOfThreads;
        int numberOfThread = omp_get_thread_num();
        int localIndex = numberOfThread * numberOfRow;
        b = 0;
        int indexOfVecotor = 0;
        if(localIndex + numberOfRow - 1 < righe){
            printf("Numero di threads = %d \n Thread corrispondente = %d  Numero da cui deve partire = %d numero di righe = %d\n ", numberOfThreads,numberOfThread,localIndex,numberOfRow);
                for(j = 0; j< colonne; j+= numberOfRow){
                    for(h = localIndex; h< localIndex + numberOfRow; h++ ){
                        for(z = j; z<j + numberOfRow; z++){
                            printf(" j = %ld h = %ld z= %ld sommo j con il suo successivo = %d\n",j,h,z,j+numberOfRow);
                            vettore[indexOfVecotor] += matrix[h][z];
                            
                        }
                    }
                    printf("Ho finito il blocco stampo il vettore[%d] = %d\n ",indexOfVecotor,vettore[indexOfVecotor]);
                    indexOfVecotor++;
                    
                }
            
        
        }
       
    }
}


int** createMatrix(int **matrix, int righe, int colonne){

    
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
        
   

            
        
    
    return matrix;

}


void viewMatrix(int **matrix, int righe, int colonne){
    for (size_t i = 0; i < righe; i++) {
        printf("\n");
        for (size_t j = 0; j < colonne; j++) {
             // Numeri casuali tra 2 e 7
            printf("%d  ",matrix[i][j]);  
        }
    }
}

