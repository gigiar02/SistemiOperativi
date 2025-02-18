//Libreria di tutte le funzioni utilizzate nel corso di Sistemi Operativi
//Per ogni funzione è associato un path per risalire alla sua implementazione
//Ricevi in input un file e trascrivine il suo contenuto

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include </home/luigi/apue.3e/include/apue.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#define BUFFSIZE 4096
//Modificare questo path con il proprio


//PATH = "Lezione_6/file.c"

int OurSquareRoot(int n);


//PATH = "Lezione_6/InfoFile.c"

//Stampa informazioni (tipologia) sui file passati in input attraverso percorso e il numero di file passati
//Si suppone che il primo elemento dell'array valido sia in posizione 1.
void StampaInfoFile(int num,char *percorsi[]);

/*
Effettua il test di accessibilità di un file per verificare in base a mode se:
Il file esiste con mode = F_OK
oppure con R_OK, W_OK e X_OK per le modalità d' accesso
*/
int VerifyAccess(const char* pathName,int mode);

//Elenca i file di una directory. Prende in input una directory
int  ElencaFile(const char *name);

//Trova se esiste il link simbolico associato al file
void TrovaLinkSimbolico();
