Il Transmission Control Protocol(TCP) è un protocollo utilizzato per lo scambio di messaggi in rete che ha le seguenti caratteristiche:
- Orientato alla connessione: è richiesto un setup fra i processi client e server
- il trasporto dei messaggi tra i processi è affidabile
- c'è un controllo del flusso dei dati e il destinatario non verrà sovraccaricato
- Se la rete è sovraccaricata il processo d'invio viene "strozzato"

Il client deve contattare il server che a sua volta deve aver predisposto una socket per il benvenuto al contatto con il client.

Il client crea una socket TCP e specifica l'indirizzo IP e il numero di porta del processo server. Inoltre questo tipo di protocollo viene detto di tipo "handshake a tre vie" poiché si va a stabilire una connessione successivamente con il server(invio di byte si dal client che dal sever).
![[Pasted image 20250428124647.png]]

