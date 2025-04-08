#segnale 
Un gruppo di processi ha un process group id che lo identifica. Il processo figlio eredita il gruppo di appartenenza del padre.
Per modificare il pgid si utilizza la system call setpgid() che permette al processo invocante di cambiare gruppo di appartenenza(a se stesso o ad altri)
![[Pasted image 20250324165834.png]]

assegna valore pgrpID al processo pid.
Se pid:
- pid = 0: cambia il valore del process group id del processo invocante
- pgrpId = 0: assegna il process group ID del processo con pid al processo invocante

Ha successo se il processo invocante e il processo specificato hanno lo stesso effective uid o groupid oppure se il proprietario del processo invocante è il superuser. 
Restituisce 0 se ha successo e -1 altrimenti.

Per creare un proprio gruppo di processi, distinto dagli altri gruppi del sistema, tipicamente si passa il proprio pid come argomento di setpgid()
![[Pasted image 20250324170937.png]]

Per ottenere il proprio pid:
![[Pasted image 20250324170959.png]]

