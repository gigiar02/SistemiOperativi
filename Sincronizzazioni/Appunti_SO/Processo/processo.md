#processo
Un processo è un programma in esecuzione che viene eseguito da shell o da un'altro processo. Quando si esegue un programma si va ad eseguire una routine di start-up speciale che prende in input:
- valori passati dal kernel in argv[] e presi dalla linea di comando
- variabili d'ambiente.
Dopo la routine di start up viene eseguita la funzione main, il cui prototipo è il seguente:
![[Pasted image 20250321122416.png]]
ove:
- argc è il numero di argomenti passati in input
- argv è un array di puntatori agli argomenti

[[Terminazione di un processo]]

***Lista d'ambiente:***
Ad ogni programma è passata una lista d'ambiente che contiene un' array di puntatori a stringhe ove ogni puntatore contiene l'indirizzo di una stringa C terminata con il carattere null \0.
L'indirizzo dell'array di puntatori è salvato nella variabile globale environ:
![[Pasted image 20250321143650.png]]

La struttura delle stringhe consiste in nome=valore:
![[Pasted image 20250321143759.png]]
![[Pasted image 20250321143836.png]]

Storicamente molti sistemi unix forniscono un terzo argomento alla funzione main, cioè l'indirizzo della lista dell'ambiente:
![[Pasted image 20250321144040.png]]

[[Programma]]

***Allocazione della memoria:***
Un processo in esecuzione può fare richiesta al kernel per ottenere risorse da poter utilizzare. Ciò avviene attraverso le seguenti funzioni:
- [[malloc]]
- [[calloc]]
- [[realloc]]

![[Pasted image 20250321150704.png]]

Tutte e tre le funzioni restituiscono un puntatore non nullo se tutto va bene, altrimenti Null in caso di errore.

Le routine di allocazione sono implementate attraverso la system call sbrk che espande o contrae l'heap del processo.
Molte implementazioni allocano un po piu dello spazio necessario per salvare alcune informazioni come:
- Dimensione del blocco allocato
- Puntatore al successivo blocco allocato


***Controllo dei Processi***
Ogni processo ha uno spazio di indirizzamento dei dati privato e non possibile condividere variabili tra processi diversi. Per fare ciò è necessaria un'interazione basato sullo scambio dei messaggi. Lo spazio di indirizzamento del codice è invece condivisibile. Infatti piu processi possono eseguire lo stesso programma facendo riferimento alla stessa area di codice nella memoria centrale. Per fare ciò il SO gestisce una struttura dati globale in cui sono contenuti i puntatori ai segmenti di testo dei processi. Questa struttura dati si chiama **text table**. L' elemento della text table si chiama text structure contiene:
- Puntatore al segmento di testo
- Numero dei processi che lo condividono

***Rappresentazione dei processi***
Ogni processo è rappresentato da un PCB(Process Control Block) che è composto da:
- Process Structure: Contiene le informazioni necessarie al sistema per la gestione del processo. Contiene anche lo [[stato del processo]]
- User Structure: informazioni necessarie solo se il processo è residente in memoria centrale
![[Pasted image 20250321155123.png]]

[[Immagine del processo]]

***CREARE PROCESSI FIGLI***
Un processo può creare dei processi figli attraverso le [[fork()]].
Per ottenere l'identificativo del processo si utilizza getpid e per ottenere il padre getppid()
![[Pasted image 20250321165754.png]]

Queste chiamate hanno sempre successo. Nel caso di init il PPID sarà ancora 1.
![[Pasted image 20250321165839.png]]
![[Pasted image 20250321165908.png]]


[[Real User ID]]
[[real group id]]
[[effective user ID]]
[[effective GroupID]]

![[Pasted image 20250321170335.png]]
![[Pasted image 20250321170354.png]]
![[Pasted image 20250321170407.png]]
![[Pasted image 20250321170432.png]]
![[Pasted image 20250321170440.png]]

Ad eccezione del segmento di testo per gli altri segmenti dei processi padre e figlio  Linux utilizza la tecnica del [[copy on write]]

- [[vfork()]]
- [[Race Conditions]]
- [[Famiglia Exec]]
- 

