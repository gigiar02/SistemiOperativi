I semafori si suddividono in:
- [[Semafori Posix]]: Non sono mantenuti nel kernel e possono essere suddivisi in due tipi:
   - [[Semafori con nome]] 
   - [[Semafori basati su memoria]]
     ![[Pasted image 20250409172003.png]]

- [[Semafori System V]]: sono mantenuti all'interno del kernel

***Domanda: Cosa si intende con "Sono mantenuti nel kernel?"

Un semaforo è un meccanismo che permetti ai thread  di un processo di sincronizzarsi.

Le operazioni che si posso fare sui semafori sono:
- Creazione:  il semaforo viene inizializzato e per poterlo fare serve anche il valore di partenza
- wait:  testa il valore del semaforo e si blocca se è == 0. Se è > 0 allora lo decrementa. Le operazioni fatte sul valore del semaforo devono essere atomiche.
- signal: incrementa il valore del semaforo. Se un processo è in attesa di essere risvegliato  viene sbloccato e il semaforo non viene incrementato.

Tipologie di semafori:
- [[Semaforo binario]]
- [[Semaforo contatore]]

# Semafori come mutex:
Un semaforo binario può essere usato come un mutex se inizializzato ad 1.  Una wait aspetta che il valore del semaforo sia > 0, mentre una chiamata sem_signal incrementa il valore del semaforo da 0 a 1.
A differenza dei mutex il semaforo non garantisce di poter essere sbloccato soltanto dal processo che l' ha bloccato.

# Persistenza degli oggetti IPC
La persistenza di un oggetto di un qualsiasi tipo di IPC è definita come la quantità di tempo in cui l'oggetto di quel tipo esiste
- Persistenza di processo: L'oggetto esiste fino a quando l'ultimo processo che mantiene l'oggetto aperto lo chiude
- Persistenza a livello kernel: L'oggetto può essere mantenuto anche dopo il reboot o fino a che l'oggetto è cancellato esplicitamente.([[Semafori System V]])
  I semafori Posix e la memoria condivisa Posix devono essere persistenti almeno a livello kernel.
- Persistenza a livello di file system: l'oggetto esiste finché non viene cancellato. Mantiene il suo valore anche se il kernel effettua un reboot.

![[Pasted image 20250409175208.png]]
![[Pasted image 20250409175220.png]]
![[Pasted image 20250409175227.png]]


