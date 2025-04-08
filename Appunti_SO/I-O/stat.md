#fileI-O 

![[Pasted image 20250305144242.png]]

La chiamata stat serve per conoscere informazioni sul tipo di file passato in input attraverso il percorso. Queste informazioni vengono messere in una struttura dati di tipo [[struct stat]].

Ci sono diverse varianti che fanno la stessa cosa, come:
- fstat: passiamo in input un descrittore invece del path
- lstat: dove l sta per link e serve per conoscere informazioni riguardanti il link simbolico  e non il file puntato da esso.
Per conoscere informazioni su di un file non è necessario avere i permessi di lettura sul file in questione. è necessario avere però i permessi sul path delle directory esplorate.

![[Pasted image 20250305163938.png]]
nlink_t serve per conoscere il numero di link hard associati all' [[I-node]]

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