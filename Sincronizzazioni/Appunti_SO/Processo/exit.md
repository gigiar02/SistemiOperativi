#processo
Le funzioni exit permettono di terminare un processo e c'è ne sono diverse:
- _exit: è una chiamata di sistema che ritorna al kernel immediatamente
- _Exit: fa parte della libreria standard ed è uguale alla precedente
- rispetto alle due precedenti prima di ritornare al kernel esegue una procedura di pulizia. In particolare tutti gli stream aperti vengono chiusi con fclose.

![[Pasted image 20250321123332.png]]

Tutte le funzioni exit ricevono in input un intero che si chiama status e che serve per poter esaminare lo stato di uscita del processo.

Lo stato di uscita è indefinito se:
- la funzione di uscita è chiamata senza passare nessun codice in input
- se la funzione main non restituisce nulla
- Se vi è un return implicito e la funzione main restituisce un intero vi è un return casuale

Chiamare la return 0 nel main equivale a chiamare una funzione exit(0).
![[Pasted image 20250321123853.png]]


[[Exit Handler]]


