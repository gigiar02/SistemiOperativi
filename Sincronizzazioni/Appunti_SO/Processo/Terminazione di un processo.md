#processo
Per terminare un [[processo]] esistono otto modi:
- Terminaizone normale:
   - Ritorno dal main
   - chiamata di [[exit]]
   - chiamata _exit o _Exit
   - Ritorno dell'ultimo thread dalla sua routine di avvio
   - chiamata di pthread_exit dall'ultimo thread
- Terminazione anomala:
   - Chiamata di abort
   - Ricezione di un segnale
   - Risposta dell'ultimo thread ad una richiesta di cancellazione

![[Pasted image 20250321124737.png]]

[[wait]]
