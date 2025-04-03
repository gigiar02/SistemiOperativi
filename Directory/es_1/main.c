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
	
	
	ssize_t written = write(fd,buffer,strlen(buffer));
	if(written <= 0) return 3;

	//Chiusura file e ritorno dello stato: successo
	close(fd);
	return 0;
	
}


int copiaFile(char *A,char *B)
{
	int fd1 = open(A,O_RDONLY);
	int fd2 = open(B,O_WRONLY | O_TRUNC);
	
	
	ssize_t pos;
	ssize_t letti;
	
	if(fd1 < 0 || fd2 < 0) return 2;
	
	//Ricavo il size
	ssize_t size = lseek(fd1,0,SEEK_END);
	size_t half = size/2;
	char buff[half];
	char buff2[half];
	
	printf("size = %ld \n",size);
	
	//mi posiziono all'inizio del file e leggo size/2 byte, ossia la prima parte
	pos = lseek(fd1,0,SEEK_SET);
	letti = read(fd1,buff2,half);
	printf("[+] Lettura prima metà = %s Letti: %ld \n",buff2,letti);
	
	//Leggo l'altra metà
	letti = read(fd1,buff,half);
	if(letti < 0) return 3;
	printf("[+] Lettura seconda metà = %s Letti: %ld \n",buff,letti);
	
	
	
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
	char buff[BUFF];
	
	//Gestione errori
	if(res == 2) { perror("Errore nell' apertura del file: "); return -1; }
	if(res == 3) { perror("Errore in fase di scrittura: ");    return -1; }
	
	
	//Copia del file in un secondo file
	res = copiaFile("output.txt","output2.txt");
	if(res != 0) return -1;
	
	//Apri il file da cui leggere
	int fd = open("output2.txt",O_RDONLY);
	read(fd,buff,BUFF);
	
	//Scrivi su terminale il risultato
	printf("Risultato finale: \n");
	write(STDOUT_FILENO,buff,strlen(buff));
	

	
	
}

