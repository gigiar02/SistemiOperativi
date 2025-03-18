![[Pasted image 20250305144242.png]]

La chiamata stat serve per conoscere informazioni sul tipo di file passato in input attraverso il percorso. Queste informazioni vengono messere in una struttura dati di tipo [[struct stat]].

Ci sono diverse varianti che fanno la stessa cosa, come:
- fstat: passiamo in input un descrittore invece del path
- lstat: dove l sta per link e serve per conoscere informazioni riguardanti il link simbolico  e non il file puntato da esso.
Per conoscere informazioni su di un file non è necessario avere i permessi di lettura sul file in questione. è necessario avere però i permessi sul path delle directory esplorate.

![[Pasted image 20250305163938.png]]
nlink_t serve per conoscere il numero di link hard associati all' [[I-node]]