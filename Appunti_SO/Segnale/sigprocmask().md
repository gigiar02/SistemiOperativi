#segnale 
![[Pasted image 20250324140806.png]]
è possibile mascherare dei segnali attraverso [[sigprocmask()]] che consente di specificare un insieme di segnali da mascherare. Restituisce la lista dei segnali che erano bloccati precedentemente.

- int how definisce:
	- SIG_BLOCK: aggiungere segnali alla maschera corrente del processo
	- SIG_UNBLOCK:  permette di rimuoverli dalla maschera corrente
	- SIG_SETMASK: permette di sostituire completamente la maschera corrente con una nuova 
- const sigset_t* set: L'insieme dei segnali da bloccare,aggiungere o rimuovere dalla maschera corrente sulla base del parametro how
- sigset_t *oset: Se non è null, conterrà la maschera precedente
![[Pasted image 20250324161117.png]]
![[Pasted image 20250324161135.png]]
![[Pasted image 20250324161147.png]]
![[Pasted image 20250324161200.png]]
![[Pasted image 20250324161212.png]]

Il modo per evitare completamente race condition è quello di far si che sia il sistema a impostare la maschera dei segnali prima che sia chiamato il gestore dei segnali. Ciò può essere fatto attraverso [[sigaction()]]
