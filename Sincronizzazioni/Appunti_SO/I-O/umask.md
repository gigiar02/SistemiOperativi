#fileI-O 
![[Pasted image 20250305154555.png]]
 La system call umask viene utilizzata per assegnare ad un processo la modalità di creazione di un file. L' argomento mask è formato da un OR bit a bit delle nove costanti di permesso di accesso ai file. La funzione ritorna il valore precedente della maschera di creazione dei file.
 Questa maschera viene utilizzata e applicata ogni qualvolta si crea un nuovo file.
 ![[Pasted image 20250305160042.png]]
 
