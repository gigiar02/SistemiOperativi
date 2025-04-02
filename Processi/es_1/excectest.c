#include <stdio.h>

//Percorso per arrivare alla cartella apue
#define apue_path </home/luigi/apue.3e/include/apue.h>
#include apue_path

//stampa il numero di argomenti passati in input ed elencali.
int main(int argc,char *argv[])
{
	printf("numero argomenti = %d \n",argc);
	
	for(int i = 0; i < argc; i++)
	{
		printf("[%d] elemento = %s \n",i,argv[i]);
	}
	
	exit(10);
}
