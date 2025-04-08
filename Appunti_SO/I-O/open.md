#fileI-O 

int open(const char *path, int oflag, /*mode_t mode*/..) 
- path è il percorso del file da creare o aprire
- oflag serve a stabilere come si vuole aprire il file:
    -  O_RDONLY: apri solo in lettura
    -  O_WRONLY: apri solo in scrittura
    -  O_RDWR: apri in lettura e scrittura
    - O_APPEND: esegue un' aggiunta alla fine del file per ciascuna scrittura
    - O_CREAT: crea il file se non esiste
    - O_EXCL:  crea il file e da in output un errore se il file esiste
    - O_TRUNC: se il file esiste ed è aperto con successo lo tronca a lunghezza zero
    - O_NOCITY: se path è un terminal device, non lo rende il terminale di controllo del processo
    - O_NONBLOCK se path è una FIFO, un file a blocchi o a caratteri, apre in maniera non bloccante, sia in lettura sia in scrittura
- Il terzo argomento viene utilizzato solo quando si crea un file:
   ![[Pasted image 20250304165925.png]]
La open è una system call utilizzata per aprire un file. Da in output un descrittore di file che in caso sia negativo significa che l'apertura del file non è andata a buon fine.

Una funzione simile alla open è la funzione creat che ha la seguente dichiarazione:
![[Pasted image 20250304170346.png]]
Permette come la open di creare file e in particolare apre un file solo in scrittura, equivalente a:
![[Pasted image 20250304170431.png]]

