#include "../lib.h"
//Calcola la radice di un numero
int OurSquareRoot(int n)
{
	if(n == 4)
	{
		return(2);
	}
	else
	{
		printf("Non posso calcolare la radice quadrata di %d \n", n);
		return(-1);
	}
}

