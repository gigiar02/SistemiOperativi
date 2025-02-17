#include "lib.h"

int main(int argc, char *argv[])
{
	if(VerifyAccess(argv[1],R_OK))
	{
		if(open(argv[1],O_RDONLY) < 0)
		{
			perror("Errore in apertura del file");
		}else
		{
			printf("file aperto con successo");
		}
		
		
	}else
	{
		printf("Non è possibile accedere al file");
	}
	
	
}
