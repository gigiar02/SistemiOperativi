#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFF PIPE_BUF

/*
	Data: 28/03/2025
	
	1) si crei un processo figlio che vada ad eseguire il programma eseguibile
	2) il padre e il figlio devono poter comunicare attraverso una pipe anonima e il padre deve scrivere al figlio: "La soluzione ottima del problema contiene la soluzione ottima dei sottoproblemi"
	3) il figlio deve leggere dalla pipe, aprire un file e scrivere ciò che ha ricevuto dal padre

*/

int main(int argc,char *argv[])
{
	int fd[2];
	char *buff = "La soluzione ottima del problema contiene la soluzione ottima dei sottoproblemi";
	
	//Creo la pipe anonima e controllo che l'operazione sia andata a buon fine
	int res = pipe(fd);
	if(res < 0)
	{
		perror("[!] Creazione della pipe non andata a buon fine: ");
		exit(-1);
	}
	
	//Creo il processo figlio
	if(fork())
	{
		printf("[+] sono il padre \n");
		//Sono il padre e devo chiudere il lato lettura della pipe poiché non mi servirà
		close(fd[0]);
		
		//Chiudo lo standard output(1) e assegno a quel descrittore il mio, in modo tale da poter scrivere sul figlio. (il figlio deve fare lo stesso)
		dup2(fd[1],1);
		
		//Scrittura su pipe anonima
		int written = write(fd[1],buff,strlen(buff));
		if(written <= 0)
		{
			perror("[!] Written Fail: ");
			exit(-1);
		}
		
		//printf("[+] Scrittura andata a buon fine su pipe anonima \n");
		
		//Aspetto che mio figlio abbia finito e successivamente controllo il suo stato d'uscita
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			//printf("[+] il processo figlio è terminato in modo normale \n");
			exit(100);
		}else
		{
			//printf("[-] il processo figlio non è terminato in modo normale");
			exit(-1);
		}
	}else
	{
		//Sono il figlio e devo chiudere il lato scrittura della pipe
		close(fd[1]);
		
		//Chiudo lo standard input e lo sostituisco con il mio descrittore
		dup2(fd[0],0);
		
		//Eseguo l'eseguibile exec_example.c
		execv("eseguibile",argv);
		
	}

}
