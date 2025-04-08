#fileI-O 

![[Pasted image 20250305144843.png]]

L'informazione sul tipo di file si trova nel campo st_mode della struttura stat. Per determinare il tipo di file si utilizzano le seguenti macro definite in sys/stat.h. L'argomento di ciascuna macro è il campo st_mode.
![[Pasted image 20250305145358.png]]
![[Pasted image 20250305145410.png]]

Per sapere la dimensione di un file:
![[Pasted image 20250305161928.png]]
Questo campo contiene infatti la dimensione in byte del file.