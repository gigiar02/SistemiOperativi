#pipeanonime
- [[IPC]]

Una pipe è un canale di comunicazione mantenuto a livello kernel tra un processo e l'altro. Avviene attraverso l'invocazione di pipe() ed  è:
- unidirezionale: quindi si può leggere o scrivere attraverso read() e write(). Quindi presenta solo due lati di accesso in/out.
- due processi possono comunicare soltanto attraverso un antenato comune che ha predisposto la pipe.
Il buffer ha dimensione massima PIPE_BUF

Ogni qualvolta si utilizza la pipline da [[shell]] quest'ultima va a creare un processo per ogni pipline e li connette attraverso la funzione [[pipe()]]

