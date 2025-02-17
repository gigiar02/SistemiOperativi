//Ricevi in input un file, somma i le coppie di numeri per riga e scrivi il
//risultato nel file "outputfile"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include </home/luigi/apue.3e/include/apue.h>
#include <errno.h>
#define BUFFSIZE 4096

int main(void)
{
	char readBuffer[BUFFSIZE];
	char ab[BUFFSIZE];
	char writeBuffer[BUFFSIZE];
	char printBuffer[BUFFSIZE];
	int fd,fr;
	int a,b,sum;
	int i = 0;
	int j = 0;
	
	memset(writeBuffer, 0, BUFFSIZE);
	memset(readBuffer, 0, BUFFSIZE);
	memset(ab, 0, BUFFSIZE);
	
	//Apertura del file su cui scriveremo i vari risultati
	if( (fd = open("outputfile.txt", O_WRONLY | O_CREAT, 0644)) < 0 )
	{
		perror("Errore nell' apertura del file");
	}
	
	//Finché c'è qualcosa da leggere
	while((fr = read(STDIN_FILENO,readBuffer,BUFFSIZE)) > 0)
	{
	   
	   //Aggiungi nel buffer di scrittura i risultati
	   for(int i = 0; i < fr; i++)
	   {
	   	
	   	//Se non sei arrivato ancora a fine riga
	   	if(readBuffer[i] != '\n')
	   	{
	   		
	   		//Aggiungi al buffer ab il carattere letto della riga
	   		ab[j] = readBuffer[i];
	   		//Incrementa l'indice dei caratteri letti
	   		j +=1;	
	   	}else
	   	{
	   	
	   		//Resetta a e b
	   		a = 0;
	   		b = 0;
	   		
	   		//Prendi dal buffer ab le prime due stringhe separate da uno spazio e trasformale in interi. infine metti i due interi
	   		//rispettivamente nelle variabili a e b.
	   		sscanf(ab, "%d %d", &a, &b);
	   		sum = a + b;
	   		//Trasforma la somma dei due numeri in stringa e inseriscila nel buffer printBuffer
	   		sprintf(printBuffer, "%d", sum);
	   		//Concatena printBuffer a writeBuffer
	   		strcat(writeBuffer,printBuffer);
	   		//Vai a capo
                    	strcat(writeBuffer, "\n"); 
                    	
                    	//Resetta il buffer ab per evitare valori sporchi 
	   		memset(ab, 0, BUFFSIZE);
	   		j = 0;
	   	}
	   	
	   }
	   
	   //Se la write del buffer non va a buon fine segnala l'errore
	   if(write(fd,writeBuffer,strlen(writeBuffer)) != strlen(writeBuffer))
	   {
	   	perror("Errore in scrittura");
	   }
	   i = i + 1;
	}
	close(fd);
	return 0;
	
}
