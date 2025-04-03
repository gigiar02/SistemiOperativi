/*
	Comunica con il client attraverso FIFO.
	
	Legge ciò che viene inviato da client e crea un file in cui va ad inserire tutto ciò che ha letto
	
	
*/

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
//Percorso per arrivare alla cartella apue
#include <unistd.h>
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path
#define buff_size PIPE_BUF

typedef void (*sighandler_t) (int);






void ricezione(char buff[buff_size])
{

	//char buff[buff_size];
	
	printf("START SERVER \n");
	
	//Apertura FIFO e controllo
	int fd = open("fifo_comunication.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("Apertura FIFO: "); 
		return;
	}
	
	printf("Pronto a leggere \n");
	read(fd,buff,PIPE_BUF);
	printf("Letto: %s \n",buff);
	
	close(fd);
	
	
	
}


void scrittura_file(char buff[buff_size])
{
	int fd = open("outputt.txt",O_RDWR|O_CREAT,S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH);
	
	if(fd < 0)
	{
		perror("Errore in apertura o creazione del file: ");
		return;
	}
	
	write(fd,buff,strlen(buff));
	close(fd);
	
	

}


int main()
{
	char buff[buff_size];
	//Ricevi da server
	ricezione(buff);
	
	//Scrivi su file ciò che hai ricevuto
	scrittura_file(buff);
	
	return 0;
}
