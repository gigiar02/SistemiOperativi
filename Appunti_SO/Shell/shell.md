#shell
[[approfondimenti shell]]
La shell è un programma speciale che permette di utilizzare i servizi offerti dal kernel , fungendo da interfaccia per l'utente. Il kernel viene caricato in memoria durante la fase di boot e si occupa della gestione del sistema. La shell risiede su disco e viene caricata una volta effettuato il login nel sistema. Quando si digita un comando la shell:
- Analizza la riga di comando: [[Analisi riga di comando]]
- Si occupa di gestire i simboli di wildcard, redirezione, le pipe ed il controllo dei job
- Cerca il comando e se lo trova lo esegue


Se si eseguono lo stesso insieme di comandi in modo ripetitivo, li si può racchiudere in uno script formati da questi comandi. Eseguendo lo script verranno eseguiti anche questi comandi. Gli script possono essere anche piu complessi e quindi formati dai diversi costrutti di programmazione come cicli test su file ecc..

Nei principali sistemi unix esistono tre shell predominanti:
 - [[shell Bourne]]
 - [[shell C]]
 - [[shell Korn]]
 Le differenze si notano soprattuo nell'utilizzo dei diversi linguaggi di scripting e nell'efficienza.
 La shell GNU Bourne Again o Bash è la shell di default di Linux e risulta essere un'estensione della shell Bourne.
 Per verificare quali shell sono disponibili nella versione linux che si usa, basta esaminare il contenuto del file /etc/shells.


---------------

 Quando si  avvia il sistema operativo, il primo processo invocato è init che ha pid 1. Init inizializza il sistema e avvia gli altri processi che aprono le linee del terminale e impostano lo stdin, stdou e sterr.
A queso punto appare il prompt dei comandi che richiede di inserire nome utente e password. Il programma /bin/login cerca nel file /etc/passwd se il nome corrisponde e in caso positivo passa la password inserita ad un pogramma di crittografia che successivamente la confronta con quella assegnata all'utente. Se il tutto va a buon fine viene impostato l'ambiente iniziale.
	Alle variabili HOME,SHELL, USER e LOGNAME sono assegnati i valori trovati nel file etc/passwd. La variabile PATH è impostata alle directory con le utility utilizzate piu di frequente. Infine viene avviato il programma presente nell'ultimar riga del file passwd, ossia la shell. La shell controlla la directory home ed esegue i file se ci sono specifici della shell.


Una volta effettuato il login, la shell ha una sua identità formata dal:
- un [[Real User ID]]
- Uno o piu [[real group id]]
- Un [[effective user ID]] ed un [[effective GroupID]]
È possibile usare il comando id per conoscere tali valori.
Ogni file in Linux ha 9 bit dedicati ai permessi che possono essere r(read),w(write),x(excecute).
I primi tre bit sono i permessi del proprietario del file,abbiamo poi i permessi del gruppo e infine i permessi per tutti gli altri.
" ls -l"  file.c permette di vedere i permessi

![[Pasted image 20250302162625.png]]

Ogni file creato ha dei permessi di default assegnati attraverso una maschera di bit. Inizialmente la maschera è impostata a 000 e i permessi sono a 7 che corrisponde a (rwx-rwx-rwx) per le directory  6 per i file.

Il comando chmod permette di modificare i permessi di un file. Per ogni file c'è un unico proprietario e soltanto quest'ultimo e il superutente possono cambiare i permessi. Il proprietario può impostare ad un gruppo dei permessi speciali.
La sintassi di chmod è la seguente:
Chmod(opzione) XYZ nome file
+ X: indica tutti gli utenti nei confronti dei quali si vuole modificare l'accesso
   - a: tutti gli utenti
   - g: tutti gli utenti del certo gruppo
   - u: l'utente stesso
   - o: tutti gli altri utenti
- Y: indica che azione si vuole compiere:
    - + attivare
    - - togliere
 - Z: indica che tipo di permessi si vuole modificare e può essere read write o execute
 Il comando chown serve per cambire il proprietario e il gruppo di un file o di una directory. In sistemi Linux solo il superutente può cambiare la proprietà.

Il comando su(set user) seleziona l'utente specificato oppure se non viene specificato il superutente e permette di loggare come quell'utente.

Ogni file ha un proprio descrittore di file che viene utilizzato per poter scrivere o leggere da file. I descrittori 0, 1 e 2 sono assegnati al terminale mentre dal 3 in poi ai file. Ogni processo ha una propria tabella dei descrittori di file che viene ereditata dai processi figli. L' assegnazione di un descrittore a un file che non sia un termiale  è chiamata redirezione dell' I/O. Viene eseguita la redirezione dell' output all' file assegnando il descrittore 1 (stdo) al file Dopo averlo tolto dal terminale. Per l'input avviene la stessa cosa,ossia si va a chiudere il descrittore associato al terminale 0 per lo std in e lo si assegna al file. I simboli per utilizzare la redirezione sono > e <.


Man
Permette di vedere la documentazione dei vari comandi. È suddiviso in sezioni e sottosezioni e ogni sezione contiene delle pagine logiche. Ogni pagina contiene un comando.

Alias:
Un alias serve ad eseguire un comando con le evntuali opzioni utilizzando un altro nome.è utile se il comando è difficile da ricordare o è lungo. Se impostato dalla shell non viene ereditato dalle subshell e per questo una volta chiusa la shell non verrà salvato. Questo succede perché gli alias vengono presi dal file bashrc che viene eseguito e resetta tutti i precedenti alias. Quindi un alias andrebbe impostato in questo file
"alias nome = comando"


LINK:
I link sono scorciatoie per accedere a file o directory. Permetono di avere uno o piu punti di accesso ai file. 
Vi sono due tipi di link:
- Soft link: il file creati utilizza il percorso del file originale e se viene eliminato quest'ultimo il file non è piu accessibile.
- Hard Link: non viene creato nessun file poiché si fa riferimento agli stessi dati fisici. I file fanno riferimento allo stesso i-node. Nell' i node c'è un campo chiamato count che memorizza il numero di hard link creati. Se questo valore dovesse scendere a 0 allora l'inode verrebbe cancellato poiché non ci sarebbero piu copie del file.

All'avvio di una shell interattiva,la shell è il processo di controllo del terminale da cui è lanciata. Se la shell esegue un comando in:
- foreground: la shell figlio si mette in un diverso gruppo, assume il controllo del terminale ed esegue il comando. Cosi ogni [[segnale]] generato dal terminale viene indirizzato al comando e non alla shell originaria. Quando il comando termina, la shell originaria riprende il controllo del terminale.
- background: la shell figlio si mette in un diverso gruppo ed esegue il comando, ma non assume il controllo del terminale. Cosi ogni segnale generato dal terminale continua ad essere indirizzato alla shell originaria. Se il comando in background tenta di leggere dal suo terminale di controllo, viene sospeso da un segnale[[SIGTTIN]]
