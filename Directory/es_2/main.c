#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFF 4500

int main()
{
	char buff[BUFF];
	char buff2[BUFF];
	char total[BUFF];
	char line[BUFF];
	int row = 0;
	int start = 0;
	int numero_caratteri = 0;
	
	//Apertura file
	int fd = open("parte1.txt",O_WRONLY);
	int fd2 = open("parte2.txt",O_WRONLY);
	if(fd < 0) return -1;
	
	
	//Lettura buffer riga per riga
	memset(line,0,BUFF);
	while(fgets(line,BUFF,stdin) != NULL)
	{
		numero_caratteri += strlen(line);
		strcat(total,line);
		
		//Salvo le 4 righe dopo cliente
		if(row >= 1 && row <= 5)
		{
			//Concatenazione di line a buff
			strcat(buff,line);
		}
		
		
		
		char *token = strtok(line, " ");
		
		while(token != NULL)
		{
			
			//Se trovi la parola cliente vai alla successiva iterazione
			if(strncmp("cliente,",token,8) == 0)
			{

				row +=1;
				token = strtok(NULL, " ");
				continue;
			}
			
			//Se trovi la parola raccolta stampa la riga a cui è
			if(strncmp("raccolta",token,8) == 0)
			{
				printf("[+] occorrenza raccolta alla riga %d \n",row);
			}
			
			//Se trovi Luigi sostituiscilo con ++++ e salva in un buffer il risultato
			if(strncmp("Luigi",token,5) == 0)
			{

				start = 1;
				strcat(buff2," ++++");
				
			}else if(start)
			{
				strcat(buff2," ");
				strcat(buff2,token);
			}
			
			//Passa alla parola successiva
			token = strtok(NULL, " ");
		}
		
		//Passa alla riga successiva
		row += 1;
		memset(line,0,BUFF);
		
		
	}
	
	//Scrittura sui due file
	write(fd,buff,strlen(buff));
	write(fd2,buff2,strlen(buff2));
	
	
	close(fd);
	close(fd2);
	numero_caratteri = 0;
	for(int i = 0; i < strlen(total); i++)
	{
		if(total[i] != '\n')
		{
			numero_caratteri++;
			printf("(%d) %c \n",numero_caratteri,total[i]);
		}else
		{
			
		}
		
	}
	
	printf("numero caratteri = %d \n",numero_caratteri);
	
	return 0;
}
