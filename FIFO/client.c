
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
//Percorso per arrivare alla cartella apue
#include <unistd.h>
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path
#define buff_size PIPE_BUF

typedef void (*sighandler_t) (int);

void handler(int sig)
{
	printf("Stronzo hai costretto il kernel a invarti un segnale perché non sai programmare \n");

}


//Crea una FIFO in scrittura  e comunica con un altro processo che legge dalla FIFO
void comunicazione()
{
	signal(SIGPIPE,handler);
	pid_t pid = getpid();
	
	printf("START CLIENT \n");
	//Controllo esistenza della fifo
	if(access("fifo_comunication.txt",F_OK) == -1)
	{
		//Se non esiste creala
		if(mkfifo("fifo_comunication.txt",0777) == 0)
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
	int fd = open("fifo_comunication.txt",O_WRONLY);
		
	if(fd == -1)
	{
		perror("Errore apertura: "); 
		return;
	}
		
	char buff[buff_size] = "Napoli \n Milan \n Juventus \n Lazio \n Benevento \n";
	ssize_t rimanenti = buff_size;
		
	//Finché non hai finito di scrivere
	
	printf("Pronto a scrivere \n");
	size_t s = 5;
	write(fd,buff,strlen(buff));
	printf("Fine scrittura \n");
			
	
	



}


int main()
{

	comunicazione();
	return 0;
	
}


