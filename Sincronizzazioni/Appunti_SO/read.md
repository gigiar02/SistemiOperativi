![[Pasted image 20250304171854.png]]
Permette di leggere da un file attraverso il suo descrittore, nbytes in buf a partire dalla posizione corrente. Aggiorna successivamente la posizione corrente. Da in output il numero di byte effettivamente letti, 0 se alla fine del file, -1 in caso di errore. Ci sono diversi casi in cui la read potrebbe leggere meno byte di quelli richiesti:
- Quando si legge da un terminale ove si legge una riga per volta
- Quando si legge da una rete che dipende dal buffering della rete che può far si che vengano letti una quantità minore di byte rispetto a quelli richiesti
- Stessa cosa quando si legge da una pipe o una fifo e si vuole leggere di piu di quanto si può leggere.
- Quando si è interrotti da un segnale e si ha letto una quantità parziale di dati