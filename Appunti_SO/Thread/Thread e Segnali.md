Ogni thread ha una propria maschera dei segnali e l' [[azione associata]] è condivisa da tutti i thread del proceso. Se un thread modifica quest'ultima, la modifica colpirà tutti gli altri thread. I segnali sono consegnati ad un singolo thread e se è relativo ad un errore hardware, solitamente è inviato al thread la cui azione ha causato l'errore.

Per inviare un segnale ad un thread, invochiamo [[pthread_kill]]
