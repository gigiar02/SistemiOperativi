#include "../lib.h"
/*
Funzioni per ottenere informazioni ed effetura operazioni sui file
*/


//Stampa informazioni (tipologia) sui file passati in input attraverso percorso e il numero di file passati
//Si suppone che il primo elemento dell'array valido sia in posizione 1.
void StampaInfoFile(int num,char *percorsi[])
{
	
	//Utilizzato per salvare il tipo di file
	char *ptr;
	struct stat buff;
	for(int i = 1; i < num; i++)
	{
		printf("Path = %s \n",percorsi[i]);
		//Riempi tutti i campi del buffer con le informazioni relative al file corrente
		if(lstat(percorsi[i],&buff) < 0)
		{
			perror("Percorso non trovato");
			continue;
		}
		
		//Controlla se il file è una directory
		if(S_ISDIR(buff.st_mode))
		{
			ptr = "directory";
			
		//File blocco	
		}else if(S_ISBLK(buff.st_mode))
		{
			ptr = "Block device";
			
		//Se è un file regular, e quindi un file di testo normale
		}else if(S_ISREG(buff.st_mode))
		{
			ptr = "Regular";
	
		//Altro tipo di file
		}else
		{
			ptr = "Altro tipo di file";
		}
		
		printf("il file è di tipo: %s \n",ptr);
		
	
	}
	
}


/*
Effettua il test di accessibilità di un file per verificare in base a mode se:
Il file esiste con mode = F_OK
oppure con R_OK, W_OK e X_OK per le modalità d' accesso
*/

int VerifyAccess(const char* pathName,int mode)
{
	printf("PathName = %s \n",pathName);
	
	//Se la verifica richiesta da mode ha esito positivo restituisci true
	if(access(pathName,mode) < 0)
	{
		return 0;
	}else
	{
		return 1;
	}

}


//Elenca i file di una directory. Prende in input una directory
int  ElencaFile(const char *name)
{
	printf("[+] inizio ad elencare i file: \n");
	DIR *directory;
	struct dirent *reader;
	
	//Apri la directory
	if((directory = opendir(name)) == NULL)
	{
		perror("[!] Apertura della directory fallita \n");
		exit(-1);
	}
	
	//Leggi la directory
	while((reader = readdir(directory)) != NULL)
	{
		printf("[+] fileName = %s \n",reader->d_name);
	}
	
	printf("[+] ho finito di leggere \n");
	
	//Chiudo la directory
	closedir(directory);
	
	return 1;
	

}

//Trova se esiste il link simbolico associato al file
void TrovaLinkSimbolico()
{
	char *path;
	DIR  *directory;
	struct stat buf;
	struct dirent *ptr;
	char cwd[100];
	//Salva il percorso per arrivare a questo file
	getcwd(cwd,sizeof(cwd));
	
	printf("[+] inizio operazione \n");
	//Apri la directory del percorso specificato
	if((directory = opendir(cwd)) == NULL)
	{
		perror("[!] Errore apertura directory");
	}
	
	//Scorri i file della directory e stampa quelli con link simbolico
	while((ptr = readdir(directory)) != NULL)
	{
		if(lstat(ptr->d_name,&buf) < 0)
		{
			perror("[!] errore lstat");
		}
		
		if(S_ISLNK(buf.st_mode))
		{
			printf("[+] FileName = %s \n",ptr->d_name);
		}
	}
	

}




