#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>

#define N 6


pid_t  pidList[N];

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
	
	
	//Generazione figli
	for(int i = 0; i < N; i++)
	{
		//Solo il padre deve eseguire le fork
		if(fork())
		{
		
		
		}else
		{
			id = i;
			pidList[id] = getpid();
			break;
		}
	
	}
	
	//Eseguono i filgi
	if(id != -1)
	{
	
		//Se l'id è pari manda un segnale SIGUSR1 ai processi con j = i-1
		if(pari > disp)
		{
			if(id % 2 == 0)
			{
				kill(pidList[id-1],SIGUSR1);
			}
		}else
		{
			//ogni processo i > N/2 Manda un segnale SIGUSR2 al processo con identificatore i-N/2
			if(id > N/2)
			{
				kill(pidList[id-N/2],SIGUSR2);
			}
		}
		
		
		
		
	}

}


int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		perror("Too few arguments: ");
		return -1;
	}
	
	int number = atoi(argv[1]);
	esercizio(number);
	
	
}
