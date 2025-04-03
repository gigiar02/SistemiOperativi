/*
	Data creazione: 2/04/2025
	
	La traccia si trova nella directory corrente
	
	Aggiungere ultimo comando 
	
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>

#define out STDOUT_FILENO 
#define in STDIN_FILENO


int main() 
{
    int fd1[2], fd2[2],fd3[2];
    pid_t pid;

    // Crea tre pipe
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);

    //Ps -fe
    printf("Eseguo ps \n");
    if ((pid = fork()) == 0) 
    {
	   	//Chiusura descrittori
	   	close(fd1[0]);
	   	close(fd2[0]);
	   	close(fd2[1]);
	   	close(fd3[0]);
	   	close(fd3[1]);
	   	
	 	//Scrive su fd1
	   	dup2(fd1[1],out);
	   	close(fd1[1]);
	   	
	   	//Avvio comando
	   	execlp("ps","ps","-fe",NULL);
	   	
	   	//in caso di problemi
	   	exit(9);
    }
    
    // Grep Root
    printf("Eseguo root \n");
    if(fork() == 0)
    {
    		//Chiusura descrittori
    		close(fd2[0]);
    		close(fd1[1]);
    		close(fd3[0]);
	   	close(fd3[1]);
    		
    		//Legge da fd1 e scrive su fd2
    		dup2(fd1[0],in);
    		dup2(fd2[1],out);
    		
    		close(fd1[0]);
    		close(fd2[1]);
    		
    		//Avvio comando
    		execlp("grep","grep","root",NULL);
    		
    		//in caso di problemi
    		exit(10);
    		
    }
    
    //Sort
    printf("Eseguo sort \n");
    if(fork() == 0)
    {
    		//Chiusura descrittori
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[1]);
		close(fd3[0]);
	    
	    	//Legge da fd2 e scrive su fd3
    		dup2(fd3[1],out);
    		dup2(fd2[0],in);
    		close(fd3[1]);
    		close(fd2[0]);
    		
    		//Esecuzione comando sort
    		execlp("sort","sort",NULL);
    		exit(7);
    
    }

    //More
    printf("Eseguo more \n");
    
    if(fork() == 0)
    {
    		//Chiusura descrittori
		close(fd1[0]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[1]);
		close(fd1[1]);
		
		//Lettura da fd3
    		dup2(fd3[0],in);
    		close(fd3[0]);
    		
    		//Esecuzione comando more
    		execlp("more","more",NULL);
    		exit(7);
    
    }
    
    
    //Sono il padre e devo chiudere tutti i descrittori
    close(fd1[1]);
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    close(fd3[1]);
    close(fd3[0]);
    
    //Aspetto che tutti i processi figli abbiano finito prima di poter uscire
    for (int i = 0; i <= 3; i++) 
    {
    		int status;
    		printf("aspetto processo %d \n",i);
    		wait(&status);
    		printf("ho finito di aspettare, uscita del processo con: %d  e i = %d \n",WIFEXITED(status),i);
    		
    }
    
    return 0;   
}

