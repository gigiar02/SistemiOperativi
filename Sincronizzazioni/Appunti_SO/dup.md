![[Pasted image 20250304174717.png]]
Le system call dup e dup2 permettono di duplicare un descrittore di file e far si che puntino ad una stessa tabella dei file.
Per creare il nuovo descrittore di file si utilizza il piu piccolo descrittore non utilizzato e in oltre se il secondo argomento in dup2 è un descrittore di file viene prima chiuso.
![[Pasted image 20250304175641.png]]
