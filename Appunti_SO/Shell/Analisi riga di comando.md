#shell 
La shell analizza sintatticamente il comando inviato dall'utente, suddividendo le parole, chiamate token attraverso gli spazi. Si occupa di analizzare i metacaratteri se ci sono e infine cerca e avvia il comando se lo trova. I programmi di shell sono dei file contenenti comandi elencati che non devono essere compilati, poiché la shell interpreta ogni linea dello script come se fosse stata immessa da tastiera.
La shell analizza il comando inviatogli e in particolare analizza il primo token. Se è un comando built-in,procede ad eseguirlo. Altrimenti ricerca nelle directory specificate all'interno della variabile PATH  il percorso per eseguire il comando e se lo trova effettua una fork creando un nuovo processo per eseguire il comando. In seguito si blocca e quando il processo termina restituisce il suo stato se necessario.
La shell valuta il tipo di comando secondo l'ordine:
 - Alias: Nomi alternativi ai comandi
 - Keyword
 - Funzione: Gruppi di comandi organizzati in routine
 - [[Built-in]]
 - Eseguibile
 Alias e funzioni sono definite nella memoria della shell mentre i comandi built in sono routine interne alla shell e gli eseguibili risiedono su disco.

Il comando ps permette di vedere i processi in esecuzione e ha le seguenti opzioni:
- ps -a: mostra anche i processi degli altri utenti
- x: mostra i processi non controllati dal terminale
- e: mostra tutti i processi

L'esecuzione di un comando corrisponde ad una [[Famiglia Exec]] (exec) a cui vengono passati in input i parametri separati da uno spazio.
![[Pasted image 20250322092010.png]]
![[Pasted image 20250322092207.png]]

***Pipline da shell:***
L'operatore pipe consente di connettere alla shell due o piu comandi:
![[Pasted image 20250322092407.png]]
Cosi facendo si redirige lo standard output del primo comando verso lo standard input del successivo e cosi via.
![[Pasted image 20250322092523.png]]

I processi coinvolti vengono eseguiti in maniera concorrente. Il processo scrive l'output in un buffer e se è pieno si blocca per aspettare che si liberi. Il processo che deve leggere se trova il buffer vuoto aspetta che siano disponibili dei dati.

***LISTE DI COMANDI:***
Le liste di comandi consentono di eseguire piu comandi in maniera sequenziale come se fossero un unico comando.
![[Pasted image 20250322092700.png]]
L'exit status corrisponde all'exit status dell'ultimo comando della lista.
La shell attende che tutti i comandi nella lista abbiano terminato la loro esecuzione prima di restituire il prompt.
A differenza della pipline non c'è alcun collegamento tra l'input e l'output dei vari comandi della lista.
![[Pasted image 20250322092845.png]]
![[Pasted image 20250322093023.png]]
![[Pasted image 20250322093046.png]]
![[Pasted image 20250322093110.png]]
![[Pasted image 20250322093119.png]]
