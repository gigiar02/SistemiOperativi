#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFF PIPE_BUF


int main(int argc,char *argv[])
{
	char buff[BUFF];
	int read_p;
	
	//printf("[+] Sono il figlio \n");
	
	//Lettura e debug
	read_p = read(0,buff,BUFF);
	if(read_p < 0)
	{
		//perror("[!] Lettura da figlio su pipe anonima non andata a buon fine:");
		exit(-1);
	}
	printf("[+] letto: %s \n",buff);
	
	// Apertura file e stampa di ciò che ho letto
	int fd = open("output.txt",O_CREAT | O_RDWR,S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
	if(fd < 0)
	{
		//perror("Errore nell'apertura del file: ");
		exit(-1);
	}
	
	//Scrivi nel file e chiudi il descrittore
	write(fd,buff,strlen(buff));
	close(fd);
	exit(2);
}
