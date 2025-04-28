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
