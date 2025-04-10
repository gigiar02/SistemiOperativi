Le variabili di condizione sono un meccanismo di sincronizzazione utilizzato per la cooperazione tra thread.
Piu thread sospendono temporaneamente l'esecuzione, aspettando che una certa condizione su dati condivisi si verifichi.
Le variabili di condizione sono sempre associate ad un mutex, in modo tale da garantire l'accesso esclusivo ai dati condivisi.
Le variabili di condizione sono composte da tre componenti:
- Il predicato: è la condizione che un thread controllerà per determinare se deve attendere
- Il mutex: è il meccanismo che protegge il predicato
- variabile di condizione : è il meccanismo con cui il thread attende il verificarsi della condizione.

![[Pasted image 20250408172536.png]]
![[Pasted image 20250408172635.png]]
![[Pasted image 20250408172725.png]]
![[Pasted image 20250408172736.png]]
![[Pasted image 20250408172917.png]]
![[Pasted image 20250408172934.png]]
![[Pasted image 20250408173112.png]]

