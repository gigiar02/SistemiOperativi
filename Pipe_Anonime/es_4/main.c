/*
	Il processo padre effettua il fattoriale del numero passato in input e comunica il risultato al figlio attraverso pipe che provvede stampare in un file il risultato

*/

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFF PIPE_BUF


int calcolaFattoriale(int i)
{
	if(i == 0 || i == 1) return 1;
	
	return calcolaFattoriale(i-1) * i;
}
int main(int argc, char *argv[])
{
	char buff[BUFF];
	int num;
	int fattoriale;
	int fd[2];
	
	if(argc < 2)
	{
		perror("[!] Too few arguments: ");
		return -1;
	}
	
	//Calcolo del fattoriale
	num = strtol(argv[1],NULL,strlen(argv[1]));
	fattoriale = calcolaFattoriale(num);
	atoi(fattoriale,buff,strlen(fattoriale));
	
	//Comunicazione
	int res = pipe(fd);
	if(res < 0) exit(20);
	
	//Creazione processo figlio
	if(fork())
	{
		//Scrivi su figlio il risultato
		int rw = write(fd[1],buff,strlen(buff));
		if(rw <= 0) return 30;
		
		//Aspetta terminazione figlio
		int status;
		wait(&status);
		
		return 0;
	}else
	{
		char r_buff[BUFF];
		
		//Lettura da pipe
		int rw = read(fd[0],r_buff,BUFF);
		if(rw <= 0) return 40;
		
		//Scrittura su file
		printf("[+] ho letto: %s",r_buff);
		return 0;
	
	}
	
	
	
	


}
