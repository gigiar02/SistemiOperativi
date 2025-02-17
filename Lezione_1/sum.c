#include <stdio.h>

int main(int argc, char *argv[])
{
	int i,sum;
	sum = 0;
	int h[5];
	for(i = 0; i < 10; i++)
	{
		if(i < 5)
		{
			sum = sum + i;
		}
		else
		{
			sum = sum + ((i-3)/2 + (i/3));
			
		}
		h[i] = i + 1;
		printf("h: %d",h[20]);
	}
	
	printf("sum = %d \n",sum);
	
}
