#processo
Sono funzioni che vengono chiamata automaticamente quando viene invocata una exit.
lo standard ISO C permette di registrare 32 funzioni di questo tipo attraverso atexit():
![[Pasted image 20250321124128.png]]

Come argomento si va a passare l'indirizzo di una funzione. La funzione non deve ricevere alcun argomento e non deve restituire nulla.
Quando si va ad invocare la exit questa chiama le funzioni in ordine inverso a quello di registrazione.

Esempio:
![[Pasted image 20250321124329.png]]
![[Pasted image 20250321124338.png]]
