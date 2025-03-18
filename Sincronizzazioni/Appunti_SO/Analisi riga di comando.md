La shell analizza sintatticamente il comando inviato dall'utente, suddividendo le parole, chiamate token attraverso gli spazi. Si occupa di analizzare i metacaratteri se ci sono e infine cerca e avvia il comando se lo trova. I programmi di shell sono dei file contenenti comandi elencati che non devono essere compilati, poiché la shell interpreta ogni linea dello script come se fosse stata immessa da tastiera.
La shell analizza il comando inviatogli e in particolare analizza il primo token. Se è un comando built-in,procede ad eseguirlo. Altrimenti ricerca nel file path il percorso per eseguire il comando e se lo trova effettua una fork creando un nuovo processo per eseguire il comando. In seguito si blocca e quando il processo termina restituisce il suo stato se necessario.
I tipi di comandi sono:
 - Alias: Nomi alternativi ai comani
 - Funzione: Gruppi di comandi organizzati in routine
 - Built-in
 - Eseguibile
 Alias e funzioni sono definite nella memoria della shell mentre i comandi built in sono routine interne alla shell e gli eseguibili risiedono su disco.

Il comando ps permette di vedere i processi in esecuzione e ha le seguenti opzioni:
- ps -a: mostra anche i processi degli altri utenti
- x: mostra i processi non controllati dal terminale
- e: mostra tutti i processi