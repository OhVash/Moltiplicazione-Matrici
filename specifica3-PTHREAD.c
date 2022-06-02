//Vascelli Alessandro - 320945 - 24/01/2022

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define R 200
#define C 200

static sem_t s1;  //semaforo

//intestazioni funzioni:
void stampa(int matrice[][C],int righe,int colonne);
int numrighe (int count);
void* moltiplica(void* arg);
void* thread1(void* arg);
void* thread2(void* arg);

int matrice[R][C]; //dichiarazione delle tre matrici
int matrice2[R][C];
int matrice3[R][C];
char file[20];
int righe,colonne;
char file2[20];
int righe2, colonne2;
int counter;//counter per le righe, mi servirà per passarlo alla funzione chiamata dai thread.


int main(){
     void * ret;
     sem_init(&s1,0,1);

    pthread_t tid1,tid2; 
    
    
    printf("Inserisci il nome del primo file da aprire: ");
    scanf("%s",file);
    printf("Inserisci il nome del secondo file da aprire: ");
    scanf("%s",file2);
    
    clock_t inizio = clock(); //avvio del clock (AVVIO PRIMA della lettura perch� utilizzo i thread anche per leggere i file)
    pthread_create(&tid1, NULL, thread1, NULL); //creazione thread che legge la prima matrice
    pthread_join (tid1, &ret);
    pthread_create(&tid2, NULL, thread2, NULL); //creazione thread che legge la seconda matrice
    pthread_join (tid2, &ret);

	printf("La prima matrice e': \n");
	stampa(matrice,righe,colonne); //visualizza Matrice1
	printf("\n");
	printf("La seconda matrice e': \n"); //visualizza Matrice2
	stampa(matrice2,righe2,colonne2);
	
	printf("\n");
 	counter = righe;
  
    printf("\n");
    
    int i,j;
    
    pthread_t thmat[righe][colonne]; //matrice di thread per la moltiplicazione

	 for (i = 0; i < righe; i++) {
    	for(j = 0; j < colonne; j++){
        	pthread_create(&thmat[i][j], NULL, moltiplica, NULL); //creazione thread con routine moltiplica
        }
    }
    
 	for (i = 0; i < righe; i++)
    	for(j = 0; j < colonne; j++)
        pthread_join(thmat[i][j], NULL); //join dei risultati dei thread
        
    
    printf("Il risultato della moltiplicazione e': \n");
   	stampa(matrice3,righe,colonne); //stampa della matrice risultante
    
    clock_t fine = clock(); //fine del clock
    double t_computazione = (double)(fine - inizio) / CLOCKS_PER_SEC; //calcolo tempo di computazione
    printf("Tempo di esecuzione: %f\n", t_computazione);
    
    return 0;
}

//funzioni:

void *thread1(void * arg)
{

sem_wait(&s1); //entro nel semaforo decrementandolo
FILE *fp;
 int r ,c ,i,j;

 fp=fopen(file,"r");//una volta aperto il file vengono prima fatti due fscanf per leggere le dimensioni della matrice
 fscanf(fp,"%d",&r);//cioè per leggere il numero di RIGHE e di
 fscanf(fp,"%d",&c);//COLONNE

 righe=r;
 colonne=c;

//viene letta la matrice elemento per elemento
 for(i=0;i<r;i++){

    for(j=0;j<c;j++){

        fscanf(fp,"%d",&matrice[i][j]);

    }

 }

 fclose(fp);
sem_post(&s1); //esco dal semaforo incrementandolo
pthread_exit (0);
}
  

void *thread2(void * arg){
    sem_wait(&s1); //entro nel semaforo decrementandolo
    FILE *fp2;
 	int r ,c ,i,j; //variabili per asssegnazione num colonne/righe e cicli

 	fp2=fopen(file2,"r");//una volta aperto il file vengono prima fatti due fscanf per leggere le dimensioni della matrice
 	fscanf(fp2,"%d",&r);//cioè per leggere il numero di RIGHE e di
 	fscanf(fp2,"%d",&c);//COLONNE

 	righe2=r;
 	colonne2=c;

//viene letta la matrice elemento per elemento
 for(i=0;i<r;i++){

    for(j=0;j<c;j++){

        fscanf(fp2,"%d",&matrice2[i][j]);

    }

 }

 fclose(fp2);
    
    sem_post(&s1); //esco dal semaforo incrementandolo
  
  pthread_exit (0);
}


void stampa(int matrice[][C],int righe,int colonne) { //funzione stampa matrice
 int i,j;

 for(i=0;i<righe;i++){

    for(j=0;j<colonne;j++){

        printf("%d ",matrice[i][j]);

    }

 printf("\n");

 }
}

int numrighe (int count){ //funzione per passare il numero di righe alla moltiplicazione sottostante 
	return count;		
}

		
void* moltiplica(void* arg){//funzione per calcolo della matrice
   	int top = numrighe(counter);
   	int i,j,k;
   	
    for (i=0; i<top; i++)	{

		for (j=0; j<top; j++){
			
			matrice3 [i][j]=0;
			for (k=0;k<top;k++){
			
			matrice3[i][j] += (matrice [i][k]* matrice2[k][j]);
			}
		}
	}
}
