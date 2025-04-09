Un mutex permette a processi concorrenti di sincronizzare l'accesso a dati condivisi. Un mutex possiede due stati:
- Bloccato: Quando è bloccato da un thread, gli altri thread che tentano di accedervi restano in attesa
- Non bloccato: Quando è non bloccato, uno dei thread in attesa lo acquisisce.
Quando un thread ha finito, lo rilascia permettendo agli altri thread di utilizzarlo.
![[Pasted image 20250408170911.png]]
![[Pasted image 20250408171016.png]]
Per bloccare un mutex, un thread usa 
![[Pasted image 20250408171113.png]]
Il mutex ritorna quando viene bloccato dal thread chiamante che può andare cosi in sezione critica. Resta bloccato fino a quando non è sbloccato da quest'ultimo.
Per sbloccare un mutex si usa:
![[Pasted image 20250408171349.png]]
![[Pasted image 20250408171427.png]]
![[Pasted image 20250408171452.png]]
![[Pasted image 20250408171728.png]]
![[Pasted image 20250408171738.png]]
![[Pasted image 20250408171752.png]]
![[Pasted image 20250408171857.png]]
![[Pasted image 20250408171911.png]]
