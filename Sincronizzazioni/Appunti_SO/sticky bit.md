è un bit che permette di richiedere al kernel che il segmento di testo di un processo resti allocato nell'area di swap anche dopo la terminazione di quest'ultimo. Questo è utile per programmi che sono utilizzati spesso. Se lo sticky bit è usato per le directory, allora l'utente può cancellare il file solo se:
- è il proprietario del file
- è il proprietario della directory
- è il superutente
