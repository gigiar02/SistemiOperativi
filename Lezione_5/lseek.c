#include <sys/types.h>
#include "/home/luigi/apue.3e/include/apue.h"

//Esempio di utilizzo della funzione lseek
//lseek permette di spostarsi all'interno di un file e restituisce la posizione corrente
int main(void)
{
	//STDIN è lo standard input e lo utilizziamo per leggere da 
	//terminale.
	//Leggiamo dalla posizione corrente 0 byte ottenendo cosi
	//La posizione corrente all'interno del terminale
	if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1)
	{
		//Caso: FIFO,Pipline socket ecc..
		printf("Cannot seek \n");
	
	}else
	{
		//Posizionamento andato a buon fine
		printf("seek OK \n");
		exit(0);
	}

}
