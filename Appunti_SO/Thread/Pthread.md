#thread
Ogni thread di un processo ha un proprio id che ha senso solo nel contesto del suo processo.
L' id è rappresentato dal tipo di dato pthread_t che non può essere trattato come un intero poiché in alcune implementazioni è un puntatore ad una struttura.

- [[pthread_equal]]: si utilizza per confrontare due thread
-  [[pthread_self]]: si utilizza per ottenere l'id.Il problema riguarda anche il non poter stampare l'id per lo stesso motivo di cui sopra.
- [[pthread_create]]: viene utilizzato per creare un nuovo thread

[[Terminazione di thread]]



