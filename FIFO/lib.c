
#include <stdio.h>
#include <fcntl.h>
//Percorso per arrivare alla cartella apue
#include <unistd.h>
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path
#define buff_size 4096

//Crea una FIFO in scrittura  e comunica con un altro processo che legge dalla FIFO
void comunicazione()
{
	pid_t pid = getpid();
	
	//Controllo esistenza della fifo
	if(access("FIFO/fifo_comunication",F_OK) == -1)
	{
		//Se non esiste creala
		if(mkfifo("FIFO/fifo_comunication",0777) == 0)
		{
			printf("[0] FIFO creata con successo \n");
		}else
		{
			printf("[0] errore nella creazione della FIFO");
			perror("");
			return;
		}
		
	}	
		
	//Apertura fifo
	int fd = open("FIFO/fifo_comunication",O_WRONLY);
		
	if(fd < 0) return;
		
	char buff[buff_size] = "Ciao sono il padre";
	ssize_t rimanenti = buff_size;
		
	//Finché non hai finito di scrivere
	while(rimanenti < strlen(buff))
	{
		rimanenti += write(fd,buff,buff_size);
		sleep(5);
	}
			
		
	



}


int main()
{

	comunicazione();
	return 0;
	
}


