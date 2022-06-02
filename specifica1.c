//Vascelli Alessandro - 320945 - 16/12/2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 200
#define C 200

//intestazioni funzioni:
void lettura(char file[],int matrice[][C],int *righe,int *colonne); 
void stampa(int matrice[][C],int righe,int colonne);
void moltiplica (int matrice [][C], int matrice2 [][C], int rig, int col);

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
    
	clock_t inizio = clock();  //avvio del clock
	
    printf("Risultato della moltiplicazione fra le due matrici: \n");
    
    moltiplica(matrice, matrice2, righe, colonne); //moltiplicazione e stampa della matrice risultante.
    
    clock_t fine = clock(); //fine del clock
    
    double t_computazione = (double)(fine - inizio) / CLOCKS_PER_SEC; //calcolo tempo di computazione
    
    printf("Tempo di esecuzione: %f\n", t_computazione);
    
    return 0;
}

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


void moltiplica (int matrice [][C], int matrice2 [][C], int rig, int col){ //funzione moltiplicazione tra matrici
	int result [R][C]; //dichiarazione matrice contenente il risultato.
	int i,j,k;
	
	for (i=0; i<rig; i++)	{

		for (j=0; j<col; j++){
			
			result [i][j]=0;
			for (k=0;k<rig;k++){
			
			result[i][j] += (matrice [i][k]* matrice2[k][j]);
			
			}
		}
	}
	
	stampa (result, rig, col); //richiamo alla funzione stampa per visualizzare il risultato ottenuto.
}
	
