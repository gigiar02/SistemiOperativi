#thread 

![[Pasted image 20250402105630.png]]
Questa funzione può essere utilizzata con [[pthread_equal]] quando un thread ha bisogno di identificare le strutture dati etichettate con il proprio ID di thread.
Un thread master può impostare dei carichi di lavoro su di una coda ed usare l'id del thread per controllare quale job va a ciascun thread di lavoro.