I domini specificano il mezzo della rete che la comunicazione socket userà. Il più comune dominio socket è AF_INET che si riferisce all'internet Networking, usato su molte reti locali Linux e da internet stessa.
Il protocollo sottostante Internet Protocolo(IP), ha solo una famiglia di indirizzi e impone che ogni computer su di una rete sia identificato dall'indirizzo IP.

I nomi sono tradotti in indirizzi IP di basso livello
![[Pasted image 20250429122915.png]]

Una porta IP è identificata da un intero univoco internamente  a 16 bit e esternamente reso univoco insieme all'indirizzo IP. Le socket devono essere collegate alle porte prima che avvenga la comunicazione.
I server aspettano le connessioni su porte specifiche.
Ci sono delle porte a cui corrispondono servizi noti, queste porte stanno solitamente a numeri inferiori di 1024.
![[Pasted image 20250429123710.png]]
