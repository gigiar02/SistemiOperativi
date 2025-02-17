//Ricevi in input un file e trascrivine il suo contenuto

#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include </home/luigi/apue.3e/include/apue.h>
#include <errno.h>
#define BUFFSIZE 4096

int main(void)
{
	char buffer[BUFFSIZE];
	int  n;
	
	//Leggi il file da terminale
	while((n = read(STDIN_FILENO,buffer,BUFFSIZE)) > 0)
	{
		//Scrivilo all'interno del terminale 
		if(write(STDOUT_FILENO,buffer,n) != n)
		{
			//Se ci sono errori nella scrittura
			perror("Write error");
		}
	
	}
	
	//Se ci sono stati errori di lettura
	if(n < 0)
	{
		perror("read error");
	}
	
	exit(0);


}
