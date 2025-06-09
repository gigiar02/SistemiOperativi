I semafori system V offrono un insieme di semafori contatori.
![[Pasted image 20250411135915.png]]
![[Pasted image 20250411140055.png]]

I semafori possono essere utilizzati sia singolarmente che come insiemi.
Un insieme di semafori:
- viene creato con semget()
- le operazioni vengono eseguite con sempop()
- le operazioni di controllo sono eseguite con semctl()

Quando si crea un semaforo deve essere specificata una key che deve essere nota a tutti i processi che vogliono utilizzarlo.
![[Pasted image 20250411140528.png]]

## Creazione di un semaforo
![[Pasted image 20250411140702.png]]
I valori per semflag sono una combinazione dei permessi con :
- IPC_CREAT: per creare un nuovo semaforo. Se non utilizzato semget() cerca il semaforo associato alla chiave e controlla i permessi dell'utente
- IPC_EXCL: viene utilizzato con IPC_CREAT affinché semget() ritorni un errore se il semaforo non esiste.

## Operazioni sui semafori:
![[Pasted image 20250411141313.png]]
![[Pasted image 20250411141358.png]]
![[Pasted image 20250411142038.png]]
![[Pasted image 20250411142049.png]]
![[Pasted image 20250411142306.png]]
![[Pasted image 20250411142409.png]]
![[Pasted image 20250411142431.png]]
![[Pasted image 20250411142439.png]]
![[Pasted image 20250411142450.png]]
