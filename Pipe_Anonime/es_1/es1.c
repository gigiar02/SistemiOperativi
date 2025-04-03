/*
	Data Creazione: 27/03/2025
	
	Utilizzando pipe() realizzare un programma che generi un processo figlio. Il padre scrive: "Ciao sono il padre" e il figlio legge.

*/

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
//Percorso per arrivare alla cartella apue
#include <unistd.h>
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path
#define BUFF PIPE_BUF


int main()
{
	int fd[2];
	char *buff = "Ciao sono il padre";
	pid_t child;
	char child_buff[BUFF] = "";
	ssize_t letto;
	
	//Apertura pipe
	if(pipe(fd) < 0)
	{
		perror("[0] Errore nell'apertura della pipe: ");
		exit(-1);
	}
	
	//Creazione processo figlio
	if((child = fork()) > 0)
	{
		//Sono il padre e procedo a chiudere stdin della pipe poiché sono uno scrittore
		close(fd[0]);
		
		//Scrivo
		ssize_t w;
		w = write(fd[1],buff,strlen(buff));
		if(w <= 0)
		{
			perror("Errore in scrittura: ");
			exit(-1);
		}
		
		close(fd[1]);
		
		//Aspetto che il figlio termini
		int status;
		waitpid(child,&status);
		
		//Verifico che sia terminato correttamente
		if(!WIFEXITED(status))
		{
			return -1;
		}
		
		
	}else
	{
		//Sono il padre e procedo a chiudere stdout della pipe poiché sono un lettore
		printf("[0] Sono il figlio con pid: %d \n",child);
		close(fd[1]);
		
		//Leggo
		letto = read(fd[0],child_buff,BUFF);
		if(letto < 0)
		{
			perror("[1] errore durante la lettura. ");
			exit(-1);
		}
		
		//Stampo il risultato
		printf("[1] Sono il figlio e ho letto: '%s' \n",child_buff);
		
		
	
	}
	
	return 0;
}
