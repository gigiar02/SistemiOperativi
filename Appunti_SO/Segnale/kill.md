#segnale 

![[Pasted image 20250324112117.png]]

La system call kill permette di inviare un segnale ad un altro processo di terminazione attraverso il suo pid e il nome del segnale.

raise permette ad un processo di fare la stessa cosa di kill, ma a se stesso.

Ritornano 0 se ok e un numero < 0 in caso di errore.

Il pid può assumere i seguenti valori:
- >0:  il segnale viene inviato al processo con process ID uguale a pid
-  == 0: il segnale viene inviato a tutti i processi con lo stesso process group del processo invocante
- < 0: il segnale viene inviato a tutti i processi con group id uguale al modulo di pid

