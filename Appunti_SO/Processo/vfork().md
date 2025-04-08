#processo
![[Pasted image 20250321171724.png]]
La vfork() crea un nuovo processo esattamente come la fork, ma senza copiarne lo spazio di indirizzamento. Infatti il processo figlio  avrà lo stesso spazio di indirizzamento del padre fino alla chiamata di [[exit]]. La vfork() assicura che il processo figlio venga eseguito per primo. Questa funzione viene utilizzata quando il processo generato ha lo scopo di eseguire un nuovo programma attraverso [[exec]]

![[Pasted image 20250321172039.png]]

![[Pasted image 20250321172049.png]]

Il figlio deve uscire esplicitamente con una _exit(). Infatti se il figlio invoca exit() il padre poi non potrà utilizzare gli stream.