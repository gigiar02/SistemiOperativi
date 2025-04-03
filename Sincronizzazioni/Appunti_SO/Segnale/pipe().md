#pipeanonime 
![[Pasted image 20250325145636.png]]

Va a creare una pipe anonima e restituisce due descrittori di file:
- d[0] per la lettura
- d[1] per la scrittura

![[Pasted image 20250325150328.png]]

Fallisce restituendo -1 se il kernel non ha piu spazio per una nuova pipe, altrimenti restituisce 0.
Se un processo legge da pipe:
- se il lato di scrittura è chiuso e si cerca di leggere, la read restituisce 0.
- se il lato di scrittura è aperto e il buffer è vuoto, con la read si rimane in attesa di leggere
- se si cercano di leggere piu byte di quanti ve ne sono la read restituisce ciò che si è riusciti effettivamente a leggere.

Se un processo scrive su di una pipe:
- se il lato di lettura è chiuso, la write restituisce -1 ed allo scrittore è inviato un segnale [[SIGPIPE]]
- se scrive meno byte che una pipe può contenere l'atomicità della scrittura è garantita
- se si scrivono piu byte che una pipe può contenere l'atomicità della scrittura non è garantita.

![[Pasted image 20250325152156.png]]

***Sequenza per creare una pipe:***
- Il processo crea una pipe anonima
- Esegue una fork() e lo scrittore chiude il suo lato di lettura,mentre il lettore chiude il lato di scrittura.
- ogni processo chiude con close() il suo descrittore quando ha finito
Una comunicazione bidirezionale può essere realizzata utilizzando due pipe.
![[Pasted image 20250325153016.png]]
![[Pasted image 20250325153127.png]]
![[Pasted image 20250325153443.png]]
![[Pasted image 20250325153454.png]]
![[Pasted image 20250325153506.png]]

Quando un processo scrittore invia piu messaggi di lunghezza variabile tramite pipe occorre fissare un protocollo di comunicazione che permetta al processo lettore di individuare la fine di ogni singolo messaggio.
Alcune possibilità sono quella di:
- inviare anche la lunghezza del messaggio
- inserire alla fine del messaggio "\0" o un newline.
Piu in generale il protocollo stabilisce la sequenza di messaggi attesa dalle due parti.

![[Pasted image 20250325153759.png]]
![[Pasted image 20250325153809.png]]


***PIPE ED EXEC***
La [[exec]] come la fork non altera la tabella dei descrittori. Il problema è che però si perdono le variabili locali.
![[Pasted image 20250325154124.png]]
![[Pasted image 20250325154414.png]]
![[Pasted image 20250325154423.png]]
![[Pasted image 20250325154432.png]]
![[Pasted image 20250325154439.png]]
![[Pasted image 20250325154449.png]]
![[Pasted image 20250325154458.png]]
![[Pasted image 20250325154506.png]]
![[Pasted image 20250325154515.png]]
![[Pasted image 20250325154525.png]]
![[Pasted image 20250325154540.png]]
![[Pasted image 20250325154547.png]]
![[Pasted image 20250325154557.png]]
