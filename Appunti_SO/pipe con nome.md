 #FIFO 
Le pipe con nome permettono di mettere in comunicazione processi che non sono legati da un antenato comune come nel caso delle [[pipe anonime]]. La creazione di una FIFO è simile alla creazione  di un [[File I-O]] 
Possiamo creare una FIFO da terminale:
![[Pasted image 20250325164629.png]]

e da programma con [[mkfifo()]]

![[Pasted image 20250325165106.png]]

Una FIFO va aperta attraverso il comando [[open]] e non la si può aprire sia in lettura che in scrittura. Un'operazione di scrittura si inserisce alla coda della fifo mentre un'operazione in lettura viene fatta alla testa della fifo.
Nella open deve essere utilizzato come parametro oflag: O_NONBLOCK che fa si che la open non sia bloccante.
![[Pasted image 20250325165516.png]]
![[Pasted image 20250325165551.png]]
![[Pasted image 20250325165559.png]]
![[Pasted image 20250325165608.png]]
![[Pasted image 20250325165622.png]]
![[Pasted image 20250325165643.png]]
![[Pasted image 20250325165654.png]]

- Se la FIFO è aperta in modalità bloccante:
	- Una read() su di una  FIFO vuota:
	   - Aspetta che i dati siano disponibile se la FIFO è aperta da un'altro processo in scrittura
	   - Ritorna 0 se la fifo non è aperta in scrittura

	- Una write() aspetta finché i dati non siano letti se la FIFO è aperta in lettura e nel caso in cui non è aperta in lettura, genera un segnale [[SIGPIPE]].
- Se la FIFO è aperta in modalità non bloccante:
     - Una read() su di una FIFO non bloccante:
       - Restituisce un errore se la FIFO è aperta in scrittura
       - Restituisce 0 se la FIFO non è aperta in scrittura.
     - Una write() genera un segnale [[SIGPIPE]] se non è aperta in lettura e inoltre se è aperta in lettura:
       - Se il numero di byte da scrivere è <= di PIPE_BUF
          - Se c'è spazio per il numero di byte specificato, sono scritti tutti i byte
          - Altrimenti ritorna con un errore
    - Altrimenti:
      - Se c'è spazio per almeno 1 byte nella FIFO, il kernel trasferisce tanti byte quanto spazio c'è nella FIFO e la [[write]] restituisce il numero di byte scritti.
      - altrimenti ritorna con un errore

![[Pasted image 20250325171034.png]]
![[Pasted image 20250325171043.png]]
![[Pasted image 20250325171053.png]]
![[Pasted image 20250325171102.png]]
![[Pasted image 20250325171110.png]]
![[Pasted image 20250325171125.png]]
![[Pasted image 20250325171135.png]]

Un utilizzo delle FIFO consiste nell'inviare i dati tra un client ed un server. Infatti il server potrebbe creare una FIFO per il client e farsi mandare le richieste attraverso la FIFO. Queste richieste non devono superare la dimensione di PIPE_BUF.

![[Pasted image 20250325171455.png]]
![[Pasted image 20250325171510.png]]
![[Pasted image 20250325171521.png]]
![[Pasted image 20250325171528.png]]
![[Pasted image 20250325171536.png]]
![[Pasted image 20250325171543.png]]
![[Pasted image 20250325171553.png]]
![[Pasted image 20250325171602.png]]
![[Pasted image 20250325171614.png]]
![[Pasted image 20250325171635.png]]
![[Pasted image 20250325171643.png]]
![[Pasted image 20250325171649.png]]
![[Pasted image 20250325171701.png]]
![[Pasted image 20250325171717.png]]
