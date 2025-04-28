Il protocollo UDP(USER DATAGRAM PROTOCOL) è utilizzato per lo scambio di messaggi in rete e ha le seguenti caratteristiche:
- Il trasferimento dei dati è inaffidabile
- Non offre setup della connessione, controllo di flusso e controllo della congestione
In questo caso il mittente deve allegare ad ogni pacchetto l'indirizzo IP e la porta di destinazione e il server deve estrarli. I dati trasmessi possono perdersi o a arrivare a destinazione in un ordine diverso da quelli d'invio.