/*
Implementare un programma parallelo per l'ambiente multicore con np unità processanti
che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue:
1)Il core master deve leggere un vettore a, di dimensione N e uno scalare beta.
2)i core devono collaborare per verificare se nel vettore esista almeno un elemento uguale al vettore beta.
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

/*
Algoritmo di ricerca binaria parallelo
Parametri:
f: indice iniziale (first)
l: indice finale (last)
token: valore da cercare
n: numero di thread
a: array in cui cercare
*/
int binary(int f,int l,int token,int n,int *a){
    int index=-1; //indice di ritorno viene inizializzato a -1 per indicare che il valore non è stato trovato
    int size=(l-f+1)/n; //calcolo la dimensione di ogni blocco
    if(size==0 || n==1){
        int p=0; //se la dimensione del blocco è 0 oppure il numero di thread è 1
        #pragma omp parallel for //direttiva parallela
        for(int i=f;i<=l;i++){ //ciclo for per cercare il valore
            if(a[i]==token){ //se il valore è stato trovato
                index=i; //assegno l'indice alla variabile index
            }}
        return index; //ritorno l'indice
    }
        int left=f; //indice sinistro
        int right=l; //indice destro
        omp_set_num_threads(n); //imposto il numero di thread
        omp_set_nested(1);//abilito il nesting che sarebbe l'annidamento
         /**
     * Quando si chiama omp_set_nested(1) con il valore 1 come argomento,
     * si imposta l'abilitazione delle regioni parallele annidate.
     * Ciò significa che è possibile creare regioni parallele all'interno di
     * altre regioni parallele e i thread possono essere creati per
     * l'esecuzione di queste regioni annidate. 
    */
        #pragma omp parallel //direttiva parallela
        {
            int id=omp_get_thread_num(); //ottengo l'id del thread
            int start=f+id*size; //calcolo l'indice iniziale dato da f+id*size perchè ogni thread deve partire da un indice diverso
            int end=start+size-1; //calcolo l'indice finale
            if(id==n-1){ //se l'id del thread è uguale al numero di thread -1
                end=l; //assegno l'indice finale a l
            }
            if(token>=a[start] && token<=a[end]){ //se il valore da cercare è compreso tra il valore iniziale e finale
                left=start; //assegno l'indice iniziale a left
                right=end; //assegno l'indice finale a right
            }
        }
        if(left==f && right==l){ //se left è uguale a f e right è uguale a l
            return -1; //ritorno -1 ovvero il valore non è stato trovato
        }
    
return binary(left,right,token,n,a); //ritorno la funzione ricorsiva
}


int main(){
int i,beta,N,nthreads;
int *a;

printf("Inserire le dimensioni dell'array: \n");
scanf("%d",&N);

printf("Inserire il numero di threads da utilizzare:\n");
scanf("%d",&nthreads);

a=(int*)calloc(N,sizeof(int));

srand(time(NULL));
for(i=0;i<N;i++){
    a[i]=rand()%10+1;
}

printf("Il vettore A:\n");
for(i=0;i<N;i++){
    printf("a[%d]=%d\n",i,a[i]);
}

printf("Inserire il valore del token da cercare:\n");
scanf("%d",&beta);


int result=binary(0,N,beta,nthreads,a);
if(result<0){
    printf("beta non è presente nell'array");
}else{
    printf("beta è presente nella posizione %d dell'array.\n",result);
}

return 0;
}