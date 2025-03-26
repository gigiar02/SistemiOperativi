/*
	Creato il 26/03/2025 
	
	Esercitazioni sui processi
*/


#include <stdio.h>

//Percorso per arrivare alla cartella apue
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path


void printFatherChild();

//crea un processo  figlio. Il padre stampa "Sono il padre" con il suo pid  e il figlio "sono il figlio" con il suo pid. Per evitare che il figlio diventi un orfano, il padre prima di terminare deve
//Aspettare con wait che il figlio abbia finito. Stampare se il figlio è stato terminato in modo normale o anormale.
void printFatherChild()
{
	
	//Prendo il pid del processo padre
	pid_t ppid = getpid();
	pid_t pid;
	
	printf("[0] Sono il padre con ppid = %d \n",ppid);
	
	//Se sei il figlio
	if(!fork())
	{
		pid = getpid();
		printf("[1] Sono il figlio con pid = %d \n",pid);
		
		//Testare lo stato di terminazione anomalo	
		//abort();
	}else
	{
		//Aspetta che il figlio finisca
		int state;
		pid = wait(&state);
		
		printf("[2] Sono il padre e mio figlio ha terminato la sua esecuzione con pid: %d  e stato di terminazione: ",pid);
		
		if(WIFEXITED(state))
		{
			printf("normale \n");
		}else
		{
			printf("anomalo \n");
		}
		
		
	
	}
	
	
}


//Stampare pid, ppid, gid, uid,ueid,gid,geid
void printID()
{
	//Pid processo e padre
	pid_t pid = getpid();
	pid_t ppid = getppid();
	
	//Real user id Real group id Effective user id Effective group id
	uid_t realuid = getuid();
	gid_t realgid = getgid();
	
	uid_t effuid = geteuid();
	gid_t effgid = getegid();
	
	printf("Processo con pid: %d  Padre con pid: %d REAL-USER-ID = %d REAL-GROUP-ID: %d EFFECTIVE-USER-ID: %d EFFECTIVE-GROUP-ID: %d \n",pid,ppid,realuid,realgid,effuid,effgid);
}


//Crea  un processo figlio che vada ad eseguire una exec e stampa il suo stato di uscita alla fine
void printState(char const *argv[])
{
	pid_t pid;
	//Se sei il processo figlio
	if(pid = fork())
	{
		int state;
	   	waitpid(pid,&state,0);
	   	state = WEXITSTATUS(state);
	   	printf("stato ritornato: %d \n",state);
	   	
		
	}else
	{
	   	
	   	//Esegui la exec
		if(execv("/home/luigi/Desktop/SistemiOperativi/Processi/es",argv) < 0)
		{
			printf("Execv non andata a buon fine. \n");
		}
	}
}





