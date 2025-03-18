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

Ogni file ha un proprietario e un gruppo che lo possiede. Queste informazioni si trovano nella [[struct stat]] e sono i campi:
![[Pasted image 20250305145544.png]]

A ciascun processo vengono associati i seguenti identificativi:
- real user id e real group id che identificano l'utente
- effective user id, effective group id e supplementary group id determinano i permessi di accesso al file.
Normalmente l'effective user ID coincide con il reeal user ID e stessa cosa per EGID e RGID.

Un programma è eseguito con i permessi di chi lo manda in esecuzione, non di chi lo possiede.
Si può inizializzare un flag in st_mode in modo che quando un determinato file di programma viene eseguito, l'effective user ID del processo sia quello del proprietario del file e tale flag è detto set-user-ID. Anolagamente ciò può essere fatto per il group id con set-group-id.
![[Pasted image 20250305151318.png]]
Nel campo st_mode vi sono 12 bit per i permessi.
Quindi il campo st_mode della [[struct stat]] contiene l'informazione relative al tipo di file e il suo valore codifica anche i bit di permesso di accesso al file.

 [[sticky bit]]

Quando vogliamo aprire un file attraverso il suo path name dobbiamo avere i permessi di esecuzione su tutte le directory incluse nel percorso compreso il file. Se vogliamo accedere in lettura ad un file dobbiamo avere i permessi di lettura e se in scrittura quelli di scrittura.
