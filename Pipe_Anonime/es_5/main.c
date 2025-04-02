/*
	Data creazione: 2/04/2025
	
	La traccia si trova nella directory corrente
	
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
    pid_t pid;

    // Crea due pipe
    pipe(fd1);
    pipe(fd2);

    // ps
    if ((pid = fork()) == 0) 
    {
	   	//Non ha bisogno di leggere ma solo di scrivere
	   	close(fd1[0]);
	   	close(fd2[0]);
	   	close(fd2[1]);
	   	
	   
	   	dup2(fd1[1],out);
	   	
	   	//Avvio comando
	   	execlp("ps","ps",NULL);
	   	
	   	//in caso di problemi
	   	exit(9);
    }
    
    // sort
    if(fork() == 0)
    {
    		close(fd2[0]);
    		close(fd1[1]);
    		
    		//Legge da fd1 e scrive su fd2
    		dup2(fd1[0],in);
    		dup2(fd2[1],out);
    		
    		//Avvio comando
    		execlp("sort","sort",NULL);
    		
    		//in caso di problemi
    		exit(10);
    		
    }
    
    if(fork() == 0)
    {
	    	close(fd1[1]);
		close(fd1[0]);
		close(fd2[1]);
	    
    		
    		dup2(fd2[0],in);
    		
    		
    		execlp("more","more",NULL);
    		exit(7);
    
    }
    
    
    close(fd1[1]);
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    
    
    for (int i = 0; i < 2; i++) 
    {
    	
    		wait(NULL);
    }
    
    
    
    

    
}

