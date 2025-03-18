Ad ogni file aperto è associato un intero non negativo detto offset corrente del file, che ci permette di capire dove ci si trova all'interno del file.
![[Pasted image 20250304170714.png]]
A meno che non si specifica l'opzione O_APPEND in fase di apertura l'offset sarà inizializzato a zero. L' argomento whence può assumere i seguenti valori:
- SEEK_SET l'offset viene posto a offset byte dall'inizio del file
- SEEK_CUR viene aggiunto offset all'offset corrente
- SEEK_END: l'offset viene posto alla fine del file, piu offset
Per determinare l'offset corrente si possono cercare 0 byte dall'offset corrente.
![[Pasted image 20250304171105.png]]
L'offset di un file può essere piu grande della dimensione del file e in questo caso la dimensione del file stesso viene estesa con la write successiva, creando un buco.