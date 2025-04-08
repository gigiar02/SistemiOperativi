#processo
Un processo può assumere uno dei seguenti stati:
- **Init:** Il processo viene caricato in memoria e inzializzazione delle strutture del SO
- Ready: pronto ad essere eseguito
- Running: La CPU sta eseguendo le istruzioni del processo
- Blocked: il processo è sospeso in attesa di un evento.
- Terminated: deallocazione del processo dalla memoria.
- Zombie: il processo è terminato ma è in attesa che il padre ne rilevi lo stato di terminazione
- Swapped: il processo è temporaneamente trasferito in memoria secondaria.
![[Pasted image 20250321152903.png]]
Lo scheduler a medio termine gestisce lo swapping dei processi:
- swap out: Quindi da memoria centrale a secondaria: si applica soprattutto ai processi bloccati
- swap in: si applica ai processi piu corti

Viene anche chiamato swapper e ha id 0. Inoltre tale processo non corrisponde a nessun programma su disco poiché e parte del kernel ed è quindi un programma di sistema.
