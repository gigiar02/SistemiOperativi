#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>

#define BUFF 4500

//Scrive all'interno del file passato in input il buffer passato
int fileWrite(char *fileName)
{
	
	//Apertura file su cui scrivere
	int fd = open(fileName,O_WRONLY | O_TRUNC);
	if(fd < 0) return 2;
	
	//Scrittura su file
	char buffer[BUFF];
	read(STDIN_FILENO,buffer,BUFF);
	printf("Ho letto %s \n",buffer);
	
	ssize_t written = write(fd,buffer,strlen(buffer));
	if(written <= 0) return 3;

	//Chiusura file e ritorno dello stato: successo
	close(fd);
	return 0;
	


	/*
	int fd = open(fileName,O_WRONLY);
	dup2(fd,0);
	char buffer[BUFF];
	read(0,buffer,BUFF);
	close(fd);
	*/
	
}


int copiaFile(char *A,char *B)
{
	int fd1 = open(A,O_RDONLY);
	int fd2 = open(B,O_WRONLY | O_TRUNC);
	char buff[BUFF];
	char buff2[BUFF];
	
	if(fd1 < 0 || fd2 < 0) return 2;
	
	//Ricavo il size
	int size = lseek(fd1,0,SEEK_END);
	size_t half = size/2;
	
	printf("size = %d \n",size);
	read(fd1,buff2,half);
	
	
	//Mi posiziono all'inizio e successivamente a metà
	int pos = lseek(fd1,size/2,SEEK_SET);
	printf("Current position = %d \n",pos);
	
	
	//Lettura seconda parte del file
	size_t byte = 2;
	ssize_t rd = read(fd1,buff,half);
	if(rd < 0) return 3;
	
	//Lettura prima parte del file
	pos = lseek(fd1,0,SEEK_SET);
	printf("pos = %d \n",pos);
	
	
	printf("Prima parte: %s  letti: %ld \n",buff2,rd);
	
	//Scrittura sul secondo file
	ssize_t written = write(fd2,buff,strlen(buff));
	if(written < 0 )  return 3;
	
	written = write(fd2,buff2,strlen(buff2));
	if(written < 0) return 3;
	
	close(fd1);
	close(fd2);
	return 0;
	
	
	

	
}

int main(int argc,char *argv[])
{
	
	
	int res = fileWrite("output.txt");
	
	//Gestione errori
	if(res == 2) { perror("Errore nell' apertura del file: "); return -1; }
	if(res == 3) { perror("Errore in fase di scrittura: ");    return -1; }
	
	
	//Copia del file in un secondo file
	res = copiaFile("output.txt","output2.txt");
	
	
}

