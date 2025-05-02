Una socket datagram specificata dal tipo SOCK_DGRAM non stabilisce  e mantiene una connesssione. il datagramma ha inoltre un limite sulla dimensione e può:
- essere perso
- essere duplicato
- arrivare fuori sequenza
Le socket datagram sono implementate nel [[dominio]] AF_INET dalle connessioni [[UDP]]/IP.
Sono però:
- Poco costose in termini di risorse poiché non devono essere mantenute le connessioni in rete.
- Sono veloci poiché non c'è associato un tempo di impostazione della connessione.