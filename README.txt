Leggere prima di utilizzare questo file.


Contenuto:

Esercizi fatti durante lo studio del corso di Sistemi Operativi.
La repository contiene tutte le lezioni:

-) Dalla lezione 1 alla 5 i codici sono sparsi e non è detto che funzionino. (Le implementerò se serviranno)
-) Dalla lezione 6 in poi le aggiungerò tutte man mano e aggiornerò questo file.


Struttura della repository:

-)Il file lib.h contiene tutte le lezioni fatte dalla 6 in poi. Ogni funzione ha un path che porta all'implementazione di quella specifica funzione. Se ci sono piu funzioni con un solo path significa
  che sono raggruppate in un unico file. Ad esempio:
  							//PATH = Lezione_i/file_i.c 
  							
  							
  							//Funzione che restituisce la radice di un numero
  							int radice(int x);
  							
  							//Funzione che calcola bo
  							bo bo(int bo);
  							
  							.
  							.
  							.
  							.
  							
  							//PATH = ......
 
-) A prescindere ogni lezione ha una sua cartella dove vi sono i file relativi a quella lezione.

-) La cartella out contiene i file oggetto di tutti i file
-) il file main.c contiene il main ed è quello in cui puoi testare le funzioni


Come far funonziare la repository? :)

1) Da terminale spostati nella cartella out e digita il comando "make" per poter compilare tutti i file, creare i relativi file oggetto se non presenti e il file eseguibile "prog"
2) Sempre da terminale per eseguire il file: "./prog"


Come fare modifiche o aggiunte di nuovi file? :(

Per quanto riguarda le modifiche, ti basterà modificare i file e successivamente se vorrai aggiornare il tutto dovrai solo digitare "make" (questo evita il dover ricompilare ogni volta e dover perdere tantissimo tempo)

Per aggiungere file nuovi invece ti basterà modificare il file "Makefile" nella cartella "out" 

  							
  							


