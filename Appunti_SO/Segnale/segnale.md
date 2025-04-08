#segnale
Un segnale è un evento asincrono che viene notificato al processo. Interrompono il normale flusso di esecuzione del programma. Un processo può inviare segnali ad altri processi e a se stesso.
Durante l'esecuzione di un processo il kernel può generare dei segnali per diversi motivi, come ad esempio:
- **Eccezione Hw**: C'è stato un problema a livello hw che viene notificato al kernel e che a sua volta va a notificare il processo coinvolto.
- ** L'utente genera  un segnale da terminale** attraverso una combinazione di tasti, come ad esempio control + c(SIGINT-SIGNAL INTERRUPT) o control + z (SIGSTOP)
- Evento Software: Si verificando quando un processo figlio termina, un timer scade ecc..

Il nome di ogni segnale inizia con SIG... ed è definito come un intero che assume valori che vanno da 1 in poi. Nei programmi vanno usati i nomi effettivi, poiché i numeri potrebbero variare da implementazione a implementazione.
Vi sono due categorie di segnali:
- Segnali tradizionali che vengono usati dal kernel per notificare gli eventi ai processi
- Segnali real time

Visto che il segnale è asincrono e il processo non può sapere quando e se arriverà, il processo deve comunicare al kernel cosa fare all'occorrenza di quest'ultimo.
Quando si verifica un segnale il  processo può comunicare al kernel di fare una di queste tre azioni:
- Ignorare il segnale: Gli unici due segnali che non possono essere ignorati sono [[SIGKILL]] e [[SIGTOP]]. Nel caso si decida di ignorare segnali dovuti ad eccezioni hardware, allora il comportamento è indefinito.
- Intercettare il segnale: fornire una funzione da eseguire per un determinato segnale
- Eseguire le [[azioni di default del segnale]]
L'azione da intraprendere prende il nome di [[azione associata]] o Disposizione del segnale.


![[Pasted image 20250324100825.png]]
***Descrizione Segnali:***
- [[SIGFPE]]
- [[SIGHUP]]
- [[SIGINT]]
- [[SIGKILL]]
- [[SIGSEGV]]
- [[SIGUSR1]]
- [[SIGALRM]]


***LA FUNZIONE SIGNAL***:
![[Pasted image 20250324104759.png]]

La funzione signal ha due argomenti e ritorna un puntatore ad una funzione che non ritorna nulla.
- signo: numero intero e che sta ad indicare il segnale che si è verificato.
- func: è il puntatore ad una funzione che prende come argomento un numero intero e che non ritorna nulla. Può assumere tre valori:
   - SIG_IGN: Indica al sistema di ignorare il segnale.
   - SIG_DFL: Indica al sistema di eseguire l'azione di default
   - L'indirizzo di una funzione da chiamare quando occorre il segnale

La funzione di cui è ritornato l'indirizzo come valore della funzione signale  ha un unico argomento  int.

Il prototipo della funzione signal può essere reso piu semplice mediante la typedef:
![[Pasted image 20250324105506.png]]
![[Pasted image 20250324105609.png]]
![[Pasted image 20250324105740.png]]

![[Pasted image 20250324110610.png]]
![[Pasted image 20250324110629.png]]
![[Pasted image 20250324110546.png]]

Quando è eseguito un programma l' [[azione associata]] a ciasun segnale è quella di default o ignora. Tutti i segnali sono impostati all'azione di default a meno che il processo che invoca exec stia ignorando il segnale. Questo perché quando un processo chiama una [[fork()]] suo figlio eredita l'azione associata di tutti i segnali. Un segnale intercettato in un processo non può essere intercettato anche da un processo creato con exec poiché l'indirizzo della funzione di gestione del segnale non avrebbe senso.

Il segnale 0 è definito come segnale nullo. Se l'argomento di signo è 0, viene eseguito da kill il controllo normale dell'errore ma non viene inviato alcun segnale.
Di solito viene utilizzato per vedere se uno specifico processo esiste. Inviando un segnale 0 ad un processo che non esiste, kill restituirà -1.

***Rientranza delle funzioni:***
Una funzione è detta rientrante se può essere eseguita simultaneamente in modo sicuro da piu thread di esecuzione nello stesso processo. Quindi piu thread o processi possono usare la stessa funzione in modo concorrente senza corrompere i dati.
Una funzione non rientrante è una funzione non può essere eseguita simultaneamente da piu processi senza comprometterne i dati a meno che non si applichino delle tecniche per renderla comunque sicura come ad esempio semafori o la disabilitazione temporanea di tutti gli interrupt durante le sezioni critiche di codice.
Le caratteristiche di una funzione rientrante:
- Assenza di chiamate a funzioni non rientranti
- Utilizzo di variabili locali o globali attraverso una copia
- tutti i dati sono passati dall'utilizzatore e non restituisce un puntatore a dati statici

Un sempio di funzione non rientrante è la malloc che se interrotta da un segnale che viene gestito a sua volta attraverso malloc potrebbe dare risultati imprevedibili.

![[Pasted image 20250324130905.png]]

![[Pasted image 20250324131431.png]]
![[Pasted image 20250324131441.png]]![[Pasted image 20250324131454.png]]
![[Pasted image 20250324135738.png]]
![[Pasted image 20250324135940.png]]
![[Pasted image 20250324135950.png]]
![[Pasted image 20250324140030.png]]
![[Pasted image 20250324140156.png]]
![[Pasted image 20250324140225.png]]
![[Pasted image 20250324140249.png]]
![[Pasted image 20250324140257.png]]
![[Pasted image 20250324140307.png]]
![[Pasted image 20250324140317.png]]

***Segnali Affidabili:***
Uno dei problemi piu insidiosi che si possono verificare è quando durante la gestione di un segnale si verifica un altro segnale. Per evitare race c'è bisogno di prendere delle precauzioni.
è possibile mascherare dei segnali attraverso [[sigprocmask()]] che consente di specificare un insieme di segnali da mascherare. Restituisce la lista dei segnali che erano bloccati precedentemente.


Nel caso di system call bloccanti se queste sono interrotte da un segnale che viene intercettato, si va ad eseguire il gestore dei segnali specificato. Dopo aver fatto ciò l'esecuzione della system call non viene ripresa e fallisce. Per evitare ciò 

![[Pasted image 20250324163333.png]]

*CONTROLLO DEI JOB:*
Ogni processo ha un :
- [[pgid]]
- terminale di controllo: è tipicamente il terminale da cui il processo viene lanciato. I figli ereditano il terminale di controllo del padre. Se il processo esegue una [[exec]] il terminale di controllo non cambia.
Ad ogni terminale è associato un processo di controllo e se ad esempio il terminale individua il metacarattere CTRL+C spedisce il segnale appropriato a tutti i processi nel gruppo del processo di controllo.

![[Pasted image 20250324171041.png]]
![[Pasted image 20250324171048.png]]
![[Pasted image 20250324171056.png]]
![[Pasted image 20250324171103.png]]
![[Pasted image 20250324171111.png]]
![[Pasted image 20250324171118.png]]

![[Pasted image 20250324171128.png]]
![[Pasted image 20250324171201.png]]
![[Pasted image 20250324171209.png]]
![[Pasted image 20250324171235.png]]
![[Pasted image 20250324171242.png]]
![[Pasted image 20250324171250.png]]


[[Thread e Segnali]]
