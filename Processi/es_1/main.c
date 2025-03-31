



#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>


#define N 100


pid_t  pidList[N];
int glob = 0;

void esercizio(int arg)
{
	int pid;
	int id = -1;
	int pari = 0;
	int disp = 0;
	
	
	
	//Scelta azione da fare
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
			glob++;
			printf("glob: %d \n",glob);
			id = i;
			pidList[id] = getpid();
			printf("sono id = %d pid = %d \n",id,pidList[id]);
			
			if(id -1 < 0) return;
			if(id - N/2 < 0) return;
			
			if(pari > disp)
			{
				if(id % 2 == 0)
				{
					
					printf("[+] Id = %d invio sengale: SIGUSR1 a %d \n",id,getpid()-1);
					kill(pidList[id-1],SIGUSR1);
					
				}
			}else
			{
				//ogni processo i > N/2 Manda un segnale SIGUSR2 al processo con identificatore i-N/2
				if(id > N/2)
				{
					printf("[+] Id = %d invio sengale: SIGUSR2 a %d \n",id,getpid() -N/2);
					kill(pidList[id-N/2],SIGUSR2);
				}
			}
			
			return;
		}
	
	}
	
	//barriera
	
	
	//Eseguono i filgi
	if(id != -1)
	{
	
		
		
		
		
		
	}

}

void handle(int type)
{
	if(type == SIGUSR1)
	{
		printf("Ricevuto SIGUSR1 \n");
	}else if(type == SIGUSR2)
	{
		printf("Ricevuto SIGUSR2 \n");
	}
}


int main(int argc, char *argv[])
{
	
	signal(SIGUSR1,handle);
	signal(SIGUSR2,handle);
	if(argc < 2)
	{
		perror("Too few arguments: ");
		return -1;
	}
	
	int number = atoi(argv[1]);
	esercizio(number);
	
	
}
