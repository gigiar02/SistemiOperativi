#thread
Se un qualsiasi thread chiame [[exit]] allora l'intero processo termina. Ciò vale anche quando si riceve un [[segnale]] la cui azione di default è quella di terminare il processo.

Un thread può utilizzare tre modi per arrestare il suo flusso senza però terminare l'intero processo:
- Il thread torna dalla routine di avvio con un codice di uscita
- Può essere cancellato da un altro thread nello stesso processo. [[pthread_cancel]]
- chiama [[pthread_exit]]

![[Pasted image 20250402112958.png]]
![[Pasted image 20250402113010.png]]
![[Pasted image 20250402113030.png]]


![[Pasted image 20250402113042.png]]
![[Pasted image 20250402113051.png]]
![[Pasted image 20250402113102.png]]
![[Pasted image 20250402113113.png]]
![[Pasted image 20250402113123.png]]
![[Pasted image 20250402113133.png]]

![[Pasted image 20250402113225.png]]
![[Pasted image 20250402113232.png]]
![[Pasted image 20250402113241.png]]
![[Pasted image 20250402113249.png]]
![[Pasted image 20250402113258.png]]
![[Pasted image 20250402113345.png]]

Per default lo stato di terminazione di un thread è mantenuto fino a che è chiamata phtread_join per quel thread. 
Se il thread è stato distaccato la funzione phtread_join non può essere usata per aspettare il suo stato di uscita.
Infatti una chiamata [[pthread_join]] per un thread distaccato fallisce restituendo EINVAL.
Un thread si può distaccare con: [[pthread_detach]]
