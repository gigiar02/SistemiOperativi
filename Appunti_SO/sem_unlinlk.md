Un semaforo può essere eliminato con la funzione:
![[Pasted image 20250409174405.png]]

I semafori hanno un contatore di riferimento che tiene traccia di quante volte sono aperti concorrentemente. Se si cancella un semaforo, potrebbe non essere cancellato poiché se è aperto da piu processi, verrà cancellato solo quando verrà chiuso dall'ultima sem_close().