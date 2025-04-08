#segnale 
![[Pasted image 20250324115106.png]]
Pone il processo in stato di sleep per il tempo specificato e in caso di interruzione inserisce in rem il tempo rimanente. Restituisce 0 nel caso in cui l'attesa viene completate e -1 in caso di errore. in tal caso errno assume uno dei valori: 
- EINVAL: si è specificato un numero di secondi negativo o troppo alto
- EINTR: la funzione è stata interrotta da un segnale.
La struttura timespec viene utilizzata per specificare intervalli di tempo con precisione al nanosecondo.
![[Pasted image 20250324115450.png]]
