#processo 
La funzione exec permette ad un processo di eseguire un altro programma. Quindi si può creare un processo figlio a cui far eseguire un compito specifico. Ciò avviene caricando un altro programma da disco che viene sostituito all' [[Immagine del processo]] corrente che viene completamente cancellata. Il pid del processo non cambia, visto che non viene creato un nuovo processo. Viene rimpiazzato lo stack i dati e il codice del processo corrente con un nuovo programma letto da disco.
Non c'è modo di tornare alla precedente immagine.
![[Pasted image 20250322082542.png]]

exec è una famiglia di primitive composta da:
- [[execl]]
- [[execle]]
- [[execlp]]
- [[execv]]
- [[execve]]
- [[execvp]]

![[Pasted image 20250322084648.png]]
![[Pasted image 20250322084708.png]]

Tutte le sei funzioni della famiglia exec restituiscono -1 in caso di errore e in caso di successo non ritornano. Queste funzioni sono tutte un front-end a [[execve]] che è una system call del kernel.
Le differenze fra le funzioni della famiglia exec :

1. sono riassunte dai suffissi v ed ed l che stanno rispettivamente per:
    - **vector**:  in input devono ricevere puntatori a stringe terminate con 0 in argv che deve essere terminato a sua volta con un puntatore nullo.

    - **list**: In questo caso si passa una lista composta da puntatori del tipo:
     ![[Pasted image 20250322084140.png]]
 2. Con il suffisso p si indicano le funzioni che replicano il comportamento della shell nello specificare il comando da eseguire. Quando l'argomento file non contiente "/" viene considerato come un nome di programma e viene eseguita una ricerca nei file presenti nella lista di directory specificate dalla variabile di ambiente PATH. Le altre funzioni si limitano a cercare di eseguire il file cercato attraverso il pathname
 3. Con il suffisso e vengono indicate quelle funzioni che hanno bisogno del vettore delle variabili d'ambiente envp[]. Le altre usano il valore della variabile environ del processo di partenza per costruire l'ambiente.
 ![[Pasted image 20250322085634.png]]
 ![[Pasted image 20250322090055.png]]
![[Pasted image 20250322090245.png]]
![[Pasted image 20250322090434.png]]
![[Pasted image 20250322090446.png]]
![[Pasted image 20250322090609.png]]
![[Pasted image 20250322090823.png]]
![[Pasted image 20250322091158.png]]
![[Pasted image 20250322091211.png]]


[[shell]]
