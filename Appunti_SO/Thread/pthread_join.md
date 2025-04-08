#thread 

![[Pasted image 20250402112600.png]]
Il thread chiamante si blocca fino a quando il thread specificato chiama [[pthread_exit]],ritorna dalla sua routine di avvio o è  cancellato.
Se il thread ritorna dalla sua routine di avvio in rval_ptr ci sarà il codice di ritorno, mentre se il thread è cancellato conterrà PTHREAD_CANCELED.