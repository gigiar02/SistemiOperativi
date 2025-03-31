/*
	Creato il 31/03/2025 alle ore 20:35
	
	La traccia è nella cartella stessa
*/



#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

#define N 18

//Svolgimento dell'esercizio
void esercizio(int arg)
{
	int pid;
	int id = -1;
	int pari = 0;
	int disp = 0;
	
	
	
	//Conteggio pari e dispari
	for(int i = 0; i < arg; i++)
	{
		int random = rand() % (arg + 1);
		if(random % 2 == 0)
		{
			pari++;
		}else
		{
			disp++;
		}
	
	}
	
	printf("pari: %d disp: %d  \n",pari,disp);
	
	
	//Generazione figli
	for(int i = 0; i < N; i++)
	{
		//Solo il padre deve eseguire le fork
		if(fork())
		{
		
		
		}else
		{
			//Figlio
			id = i;
			
			printf("sono id = %d pid = %d \n",id,getpid());
			
			//Casi Base
			if(id -1 < 0 && pari > disp) return;
			if(id - N/2 < 0 && pari <= disp) return;
			
			
			if(pari > disp && id % 2 == 0)
			{	
				printf("[+] Id = %d invio sengale: SIGUSR1 a %d \n",id,getpid()-1);
				kill(getpid()-1,SIGUSR1);
					
				
			}else if(pari <= disp && id > N/2)
			{
				//ogni processo i > N/2 Manda un segnale SIGUSR2 al processo con identificatore i-N/2
				printf("[+] Id = %d invio sengale: SIGUSR2 a %d \n",id,getpid() -N/2);
				kill(getpid()-N/2,SIGUSR2);
				
			}
			
			sleep(100);
			return;
		}
	
	}
	
	//barriera
	
	
	//Eseguono i filgi
	if(id != -1)
	{
	
		
		
		
		
		
	}

}


//Gestore del segnale
void handle(int type)
{
	if(type == SIGUSR1)
	{
		printf("Sono %d e ho ricevuto SIGUSR1 \n",getpid());
	}else if(type == SIGUSR2)
	{
		printf("Sono %d e ho ricevuto SIGUSR2 \n",getpid());
	}
}


int main(int argc, char *argv[])
{
	
	signal(SIGUSR1,handle);
	signal(SIGUSR2,handle);
	
	//Controllo argomenti
	if(argc < 2)
	{
		perror("Too few arguments: ");
		return -1;
	}
	
	int number = atoi(argv[1]);
	esercizio(number);
	
	return 0;
}
