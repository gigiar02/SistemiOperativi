#fileI-O 
I file aperti possono essere condivisi tra diversi processi. Il kernel utilizza tre strutture dati per rappresentare un file aperto:
- Ogni processo ha un' entrata nella tabella dei processi e all'interno di ogni entrata della tabella dei processi c'è una tabella dei descrittori di file aperti. A ciascun descrittore sono associati:
   - I flag del descrittore di file
   - un puntatore ad un'entrata della tabella dei file
* Il kernel mantiene una tabella di file per tutti i file aperti e ogni entrata contiene:
    - I flag dello stato del file
    - L'offset corrente del file
    - Un puntatore alla entrata della tabella dei v-node per i file
- Ogni file aperto ha una struttur v-node che contiene informazioni sul tipo del file e puntatori a funzioni che operano sul file.
![[Pasted image 20250304173625.png]]
Nel caso in cui si hanno due processi indipendenti che hanno lo stesso file aperto, questi avranno un'entrata alla file table diversa poiché l'offset che hanno sul file potrebbe essere diverso
![[Pasted image 20250304173946.png]]

Quando un processo accede ad un file e ad esempio viene invocata una [[write]] l 'offset corrente viene modificato nella tabella dei file ed eventualmente anche il v-node. La [[lseek]] invece non richiede nessun operazione di I/O poiché richiede solo una modifica al valore di offset. Invece un operazione di O_APPEND comporta che l'offset viene modificato alla dimensione del file presa dal v node.