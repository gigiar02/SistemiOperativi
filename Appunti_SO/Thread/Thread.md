I thread vengono utilizzati all'interno di un [[processo]] per eseguire compiti diversi. Condividono la stessa memoria e la differenza principale con i processi è che i [[context switch]] non hanno molto overhead come nei processi.
Il motivo è dovuto al fatto che quando si vanno a creare processi figli questi differiranno prima o poi  solo per lo stato della CPU e lo Stack, mentre il resto sarà identico. (nel caso in cui non hanno nessuna risorsa alllocata saranno identici).

I thread suddividono lo stato del processo in due parti:
- Stato delle risorse associate al processo
- Stato dell'esecuzione associato ad ogni thread
Solo gli stati di esecuzione devono essere scambiati nella commutazione tra thread poiché le risorse sono condivise.

- La libreria per poter utilizzare i thread si chiama [[Pthread]]

***Thread vs Processo***
![[Pasted image 20250402113956.png]]



***Clone***
![[Pasted image 20250402120533.png]]
![[Pasted image 20250402120543.png]]
![[Pasted image 20250402120554.png]]


![[Pasted image 20250402120633.png]]
![[Pasted image 20250402120642.png]]
![[Pasted image 20250402120652.png]]
![[Pasted image 20250402120701.png]]
![[Pasted image 20250402120709.png]]
![[Pasted image 20250402120715.png]]
![[Pasted image 20250402120723.png]]
