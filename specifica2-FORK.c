//Vascelli Alessandro - 320945 - 20/01/2022

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define R 200
#define C 200

//intestazioni funzioni:
void lettura(char file[],int matrice[][C],int *righe,int *colonne); 
void stampa(int matrice[][C],int righe,int colonne);

int main()
{
    int matrice[R][C]; //dichiarazione prima matrice.
    char file[20];
    int righe,colonne;

    printf("Inserisci il nome del primo file da aprire: ");
    scanf("%s",file); //lettura file1...

    lettura(file,matrice,&righe,&colonne); //letto il primo file contenente Matrice1

    stampa(matrice,righe,colonne); //visualizza Matrice1
 	printf("\n");
  
    int matrice2[R][C]; //dichiarazione seconda matrice
    char file2[20];
    int righe2, colonne2;
    
    printf("Inserisci il nome del secondo file da aprire: ");
    scanf("%s",file2); //lettura file2...

    lettura(file2,matrice2,&righe2,&colonne2); //letto il secondo file contenente Matrice2
    
    stampa(matrice2,righe2,colonne2); //visualizza Matrice2
    printf("\n");
    
    int result[R][C]; //matrice per risultato moltiplicazione
    int pid; //processID
    int pipe_arr[2]; //per passare i valori al padre
    char dati[300]; //buffer per i dati
    int i,j,k;
    
    clock_t inizio = clock(); //avvio del clock
    
	for (i=0;i<righe;i++){
    	
    	pipe(pipe_arr);
    	
    	if (pipe<0){
    		printf("ERR!");
		}
		
		pid = fork();
		
		if (pid==-1){
			printf("ERR!");
		}
		
		else if (pid==0) { //processo figlio --> calcolo della moltiplicazione.
			for (j=0;j<righe;j++){
				for(k = 0; k < colonne; k++){
					result[i][j] += (matrice [i][k]* matrice2[k][j]);
				}
				write(pipe_arr[1], &result[i][j], sizeof(result[i][j]));
			}
		}
		
		else if (pid>0){ //processo padre --> attende i risultati e li mette insieme.
			wait(0);
			read(pipe_arr[0], dati, sizeof(dati));//una volta letto ciò che contiene la pipe viene inserito nell'array
			exit(0);	
		}		
	}
	
	clock_t fine = clock(); //fine del clock
	
	printf("Risultato della moltiplicazione fra le due matrici: \n");
	
	stampa(result,righe,colonne); //stampa della matrice risultante
	
	double t_computazione = (double)(fine - inizio) / CLOCKS_PER_SEC; //calcolo tempo di computazione
    
    printf("Tempo di esecuzione: %f\n", t_computazione);
       
return 0;
}

//funzioni:

void lettura(char file[],int matrice[][C],int *righe,int *colonne){ //funzione per lettura righe/colonne della matrice e gli elementi
 FILE *fp;
 int r ,c ,i,j;

 fp=fopen(file,"r");//una volta aperto il file vengono prima fatti due fscanf per leggere le dimensioni della matrice
 fscanf(fp,"%d",&r);//cioè per leggere il numero di RIGHE e di
 fscanf(fp,"%d",&c);//COLONNE

 *righe=r;
 *colonne=c;


 for(i=0;i<r;i++){ //viene letta la matrice elemento per elemento

    for(j=0;j<c;j++){

        fscanf(fp,"%d",&matrice[i][j]);

    }

 }

 fclose(fp);

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
