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


int main() {
    int fd1[2], fd2[2];
    int fd3[2], fd4[2];
    pid_t pid;

    // Crea due pipe
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);

    //Ps -fe
    printf("Eseguo ps \n");
    if ((pid = fork()) == 0) 
    {
	   	//Non ha bisogno di leggere ma solo di scrivere
	   	close(fd1[0]);
	   	close(fd2[0]);
	   	close(fd2[1]);
	   	close(fd3[0]);
	   	close(fd3[1]);
	   	
	   
	   	dup2(fd1[1],out);
	   	
	   	//Avvio comando
	   	execlp("ps","ps","-fe",NULL);
	   	
	   	//in caso di problemi
	   	exit(9);
    }
    
    // Grep Root
    printf("Eseguo root \n");
    if(fork() == 0)
    {
    		close(fd2[0]);
    		close(fd1[1]);
    		close(fd3[0]);
	   	close(fd3[1]);
    		
    		//Legge da fd1 e scrive su fd2
    		dup2(fd1[0],in);
    		dup2(fd2[1],out);
    		
    		//Avvio comando
    		execlp("grep","grep","root",NULL);
    		
    		//in caso di problemi
    		exit(10);
    		
    }
    
    //Sort
    printf("Eseguo sort \n");
    if(fork() == 0)
    {
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[1]);
		close(fd3[0]);
	    
    		dup2(fd3[1],out);
    		dup2(fd2[0],in);
    		
    		
    		execlp("sort","sort",NULL);
    		exit(7);
    
    }

    //More
    printf("Eseguo more \n");
    if(fork() == 0)
    {
		close(fd1[0]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[1]);
		close(fd1[1]);
		
		
	    
    		
    		dup2(fd3[0],in);
    		
    		
    		execlp("more","more",NULL);
    		exit(7);
    
    }
    
    
    close(fd1[1]);
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    close(fd3[1]);
    close(fd3[0]);
    
    sleep(100);
    for (int i = 0; i < 2; i++) 
    {
    		int status;
    		printf("aspetto processo %d \n",i);
    		wait(&status);
    		printf("ho finito di aspettare uscita stat: %d %d \n",WIFEXITED(status),i);
    		if(status != 0) return status;
    }
    
    
    return 0;
    

    
}

