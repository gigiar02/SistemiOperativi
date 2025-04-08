#processo
![[Pasted image 20250321172426.png]]

La funzione wait sospende il processo invocante finché:
- un figlio ha terminato la propria esecuzione
- riceve un segnale
La funzione waitpid sospende il processo finché:
- il processo pid ha terminato la propria esecuzione, oppure
- riceve un segnale
Se il processo è uno zombie, le funzioni ritornano subito.
Se il processo non ha figli viene ritornato il valore -1 altrimenti il pid del processo terminato.

La terminazione di un processo figlio viene notificata al genitore attraverso il segnale SIGCHILD.

Per entrambe le funzioni l'argomento statloc è un puntatore ad un intero e se è non nullo, lo stato di terminazione viene conservato in questa variabile. Lo stato di terminazione può essere rilevato utilizzando le macro definite in ![[Pasted image 20250321173127.png]]

![[Pasted image 20250321173617.png]]
tramite la wait si può quindi ottenere lo status con cui esce il processo figlio. Però:
- Nel caso di una conclusione normale lo stato di uscita del processo è caratterizzato da un exit status, cioé il valore passato alle funzioni exit o _exit.
- Se il processo è concluso in maniera anomala, il programma non può specificare nessun exit status ed è il kernel che deve generare automaticamente un termination status per indicare la ragione della conclusione anomala.
![[Pasted image 20250321174306.png]]
![[Pasted image 20250321174328.png]]
In waitpid l'argomento pid:
- -1: attende un qualsiasi figlio e quindi diviene uguale a wait
- > 0: attende il processo che ha il process ID uguale a pid
- = 0: attende un qualsiasi figlio il cui process group ID è uguale a quello del processo chiamante
- < -1: attende un qualsiasi figlio il cui process Group ID è uguale a quelo del valore assoluto di pid
L'argomento options è 0 oppure una combinazione in or di:
- WNOHUNG: non blocca il processo invocante se il pid del figlio non è immediatamente disponibile
- WUNTRACED: ritorna lo stato di un figlio sospeso
