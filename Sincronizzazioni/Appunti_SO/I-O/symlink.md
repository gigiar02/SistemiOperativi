#fileI-O 

![[Pasted image 20250305164427.png]]
symlink viene utilizzata per creare un link simbolico. Per leggere un link simbolico è necessario utilizzare readLink, che apre il link,legge il contenuto e lo chiude. Il contenuto viene messo in buf senza carattere di terminazione