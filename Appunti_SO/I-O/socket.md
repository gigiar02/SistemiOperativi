#fileI-O
Sono file che servono per la comunicazione tra processi su rete.

#socket
Due processi su differenti host comunicano scambiandosi messaggi attraverso una rete di comunicazione comune. I servizi disponibili in rete si basano principalmente sul modello [[client server]]

## Invio e ricezione dei messaggi
Un processo invia e riceve messaggi attraverso la sua socket e non si occupa di come quel messaggio sia inviato in rete e presuppone che arriverà a destinazione.
Il processo destinatario è identificato in modo univoco dall'indirizzo IP e dal numero di porta,poiché su di uno stesso indirizzo IP potrebbero girare piu processi.
Per lo scambio di messaggi  si deve stabilire il protocollo da utilizzare :
- [[TCP]]
- [[UDP]]

## Socket

Esistono due modi per comunicare in rete:
- [[connection oriented]]
- [[connectionless oritented model]]

La creazione di una socket avviene mediante [[socket()]] e non è condivisibile fra processi.
Il processo server crea una socket e associa gli associa un nome che:
- nel caso di socket locali si associa un filename nel filesystem
- nel caso di socket di rete il nome corrisponde ad un identificatore di servizio(numero di porta o punto di accesso.) rilevante per la particolare rete a cui i client possono connettersi.
Il nome viene assegnato alla socket attraverso la system call [[bind()]].
Il processo si mette in ascolto attraverso la system call [[listen()]] che va a creare una coda di connessioni in arrivo che il server può accettare attraverso [[accept()]]. 
Si può scrivere il codice in modo tale da accettare connessioni multiple o nel modo piu semplice possibile accettando una connessione per volta facendo cosi aspettare gli altri client sulla coda.

![[Pasted image 20250429121309.png]]

## Esempio client server locali
![[Pasted image 20250429121549.png]]
![[Pasted image 20250429121712.png]]
![[Pasted image 20250429121745.png]]
![[Pasted image 20250429121804.png]]
![[Pasted image 20250429121959.png]]
![[Pasted image 20250429122035.png]]

## Attributi delle socket
Le socket sono caratterizzate da tre attributi:
- [[dominio]]
- [[tipo]]
- [[protocollo]]
## Formati degli indirizzi
Il formato dell'indirizzo è specifico per ogni dominio. Per poter fornire questi indirizzi alle funzioni per le socket, gli indirizzi subiscono un cast ad una struttura indirizzo generica.
![[Pasted image 20250429134311.png]]

## Chiudere una socket
Si può terminare una connessione socket al server e al client invocando  close() cosi come avviene per i descrittori di fie
![[Pasted image 20250429155253.png]]
![[Pasted image 20250429155302.png]]
![[Pasted image 20250429155311.png]]
![[Pasted image 20250429155320.png]]
![[Pasted image 20250429155338.png]]
![[Pasted image 20250429155417.png]]
![[Pasted image 20250429155427.png]]
![[Pasted image 20250429155433.png]]
![[Pasted image 20250429155440.png]]

## Ordinamento dei Byte
I numeri di porta e gli indirizzi sono comunicati sulle interfacce delle socket come numeri binari. I computer possono impiegare ordinamenti diversi per gli interi:
- Little endian: Un processo intel memorizza l'intero a 32 bit come quattro byte di memoria consecutivi nell'ordine 1-2-3-4, ove 1 è il byte piu significativo.
- Big endian: I processori Motorola memorizzano l'interno nell'ordine  di byte 4-3-2-1
Se la memoria per gli interi è copiata byte per byte, i due computer hanno valori differenti assegnati all'intero.
Per consentire a computer che rappresentano interi in modo differente di trasmettere in rete in modo coerente è necessario avere un ordinamento nella rete.
Per questo si usano le seguenti funzioni:
![[Pasted image 20250429161826.png]]
Le seguenti funzioni convertono gli interi a 16 e 32 bit tra il formato nativo e l'ordinamento standard utilizzato in rete. Per i computer in cui l'ordinamento nativo coincide con l'ordinamento standard queste operazioni sono nulle.
![[Pasted image 20250429162136.png]]
![[Pasted image 20250429162202.png]]
![[Pasted image 20250429162213.png]]
![[Pasted image 20250429162338.png]]
![[Pasted image 20250429162347.png]]
![[Pasted image 20250429162354.png]]
![[Pasted image 20250429162401.png]]
![[Pasted image 20250429162422.png]]
