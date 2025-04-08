#segnale 
![[Pasted image 20250324113851.png]]
Sospende un processo finché non riceve un certo segnale non viene intercettato. Restituisce il controllo solo dopo che è eseguito un gestore di segnale e a sua volta restituisce -1 e pone errno a EINTR.