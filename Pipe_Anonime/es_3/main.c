/*
	Data: 28/03/2025
	Traccia: nella cartella. Come stringhe invio quelle prese da terminale

*/

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#define BUFF PIPE_BUF


int main(int argc, char *argv[])
{
	int fd[2];
	char buff[BUFF];
	
	//Creo la pipe anonima e controllo che sia state creata correttamente
	int res = pipe(fd);
	if(res < 0)
	{
		perror("[!] non sono riuscito ad aprire la pipe: ");
		exit(2);
	}
	
	//Creo il processo figlio
	if(fork())
	{
		//Padre: Chiude il descrittore che non gli serve e sostituisce stdout con il suo descrittore
		close(fd[0]);
		dup2(fd[1],1);
		
		//Scrittura
		res = write(fd[1],"Hello World\n",strlen("Hello World\n"));
		res = write(fd[1],"Ciao mondo\n",strlen("Ciao mondo\n"));
		res = write(fd[1],"Test  \n",strlen("Test  \n"));
		if(res < 0)
		{
		    exit(3);
		}
		
		close(1);
		
	}else
	{
		//Sono il figlio
		close(fd[1]);
		dup2(fd[0],0);
		
		//Lettura
		//res = read(0,buff,BUFF);
		
		execlp("sort","sort",0);
		
	}
	
	

}
