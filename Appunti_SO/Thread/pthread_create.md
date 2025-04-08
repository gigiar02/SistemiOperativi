#thread 

![[Pasted image 20250402110133.png]]

- Se la funzione va a buon fine, la locazione di memoria puntata da tidp è impostata all' ID del nuovo thread creato.
- L'argomento attr è utilizzato per definire vari [[attributi del thread]]
- Il nuovo thread inizia all'indirizzo della funzione start_rtn che prende un solo argomento, arg (puntatore senza tipo)
- Se è necessario passare piu di un argomento a questa funzione, bisogna memorizzarli in una struttura e passare l'indirizzo della struttura in arg

Quando viene creato un thread non c'è nessuna garanzia su quale venga invocato per primo.

Il nuovo thread ha memoria condivisa e eredita l'ambiente e la maschera dei segnali, mentre i segnali pendenti non sono ereditati e quindi cancellati.

![[Pasted image 20250402111604.png]]
![[Pasted image 20250402111613.png]]
![[Pasted image 20250402111838.png]]
![[Pasted image 20250402111848.png]]

***Passaggio Parametri:***
![[Pasted image 20250402112042.png]]
![[Pasted image 20250402112051.png]]
