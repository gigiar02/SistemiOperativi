#processo
![[Pasted image 20250321164426.png]]
La fork permette di creare un processo figlio che è la copia del processo padre che esegue la fork. L'area dati viene duplicata, mentre l'area codice viene condivisa. Il processo figlio riceve esito = 0, mentre il processo padre riceve esito > 0 che corrisponde all'identificatore del figlio. Se l'operazione fallisce ha esito -1 e alla variabile errno viene assegnato il codice relativo all'errore. 
Una volta invocata una fork non si può sapere se il figlio andrà in esecuzione prima del genitore o dopo. La tabella dei descrittori è condivisa tra il processo genitore e figlio.
![[Pasted image 20250321165137.png]]
Quando un processo figlio termina tramite una [[exit]] la sua terminazione è comunicata al padre tramite un segnale e il padre si comporta di conseguenza.
![[Pasted image 20250321165434.png]]
![[Pasted image 20250321165601.png]]
![[Pasted image 20250321165613.png]]
