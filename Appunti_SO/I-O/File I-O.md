#fileI-O

Per eseguire operazioni su file di tipo I/O vengono utilizzate delle system call, quali:
- [[open]]
- [[read]]
- [[write]]
- [[lseek]]
- [[close]]
- [[dup]]
- [[stat]]
- [[access]]
- [[umask]]
- [[chmod]]
- [[chown]]
- [[truncate]]
- [[link]]
- [[unlink]]
- [[symlink]]
- [[mkdir]]
- [[opendir]]
- [[chdir]]
- [[kill]]
- [[alarm]]
- [[pause]]
- [[sleep]]
- [[nanosleep]]
- [[abort]]




In generale i file aperti sono gestiti dal kernel mediante descrittori di file, che sono interi non negativi. Il valore di un descrittore di file può variare da 0 a POSIX_MAX, che è una costante che sta ad indicare il numero massimo di file che possono essere aperti contemporaneamente.
Qualsiasi delle operazioni descritte da in output un descrittore di file che serve a riferirsi univocamente a quest'ultimo.
In generale:
- Il descrittore 0 è associato allo standard input (STDIN_FILENO)
- Il descrittore 1 è associato allo standard output (STDOUT_FILENO)
- Il descrittore 2 è associato allo standard error (STDERR_FILENO)

[[Condivisione file]]

Per gestire gli errori originati dalle system call i due principali strumenti da utilizzare sono:
- errno variabile globale che contiene il codice numerico dell'ultimo errore generato da una system call
- perror() : subroutine che mostra una descrizione testuale dell'ultimo errore generato dall'invocazione di una system call.

![[Pasted image 20250304180749.png]]![[Pasted image 20250304180803.png]]
![[Pasted image 20250304180819.png]]

ESERCIZI:
![[Pasted image 20250304180829.png]]
![[Pasted image 20250304180846.png]]

I tipi di file sono:
- [[regolari]]
- [[directory]]
- [[file speciali a blocco]]
- [[file speciali a caratteri]]
- [[FIFO]]
- [[socket]]
- [[link simbolici]]


