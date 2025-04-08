#processo
Un programma scritto in C è composto dai seguenti pezzi:
- **Segmento di testo**: le istruzioni macchina eseguite dalla CPU
- **segmento di dati inizializzati**: variabili globali e statiche inizializzate nel programma
- **segmento di dati non inizializzati**: variabili globali e statiche che vengono inizializzate a 0 o a valore nullo dal kernel prima dell'esecuzione. (bss block started by simbol)
- **stack:** contiene variabili legate alle funzioni come indirizzo di ritorno, registri, variabili automatiche e temporanee.
- **Heap**: attraverso l'heap avviene l'allocazione dinamica della memoria.
![[Pasted image 20250321144943.png]]

Il comando size permette di vedere la dimensione dei segmenti di testo,dati  e bss:
![[Pasted image 20250321145833.png]]
