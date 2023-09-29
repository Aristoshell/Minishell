**Pas encore gere, mais a faire ensuite**

- redirections
- expand
- entre quotes


**Composition commande**

boucle tant quon a fini le tableau

	boucle jusqua ce quon n'ai pas de pipe
	
	1) Checker si redirection d'intfile
		si pas premier bout + ce que celui davant est une pipe
			--> redirection in pipe
		sinon si j'ai <<
			--> redirection heredoc avec separator = tab[+1]
		sinon si j'ai <
			--> redirection fichier de tab[+1]
		sinon
			--> no redirect
		attention ! bien verifier quon a un tab[+1], sinon renvoyer erreur i guess ?
	
	2) le truc actuel est une commande
		- checker si tab[i] est un built in ou pas
		tant qu'on na pas > ou >> ou | (faire bool opearateur redirection)
			- mettre dans **cmd_args les mots de tab[current]
	3) checker redirection out
		si > ou >> ou |
			si > open le suivant en mode edition, puis tant quon na pas de pipe on avance
			si >> open le suivant en mode append, puis tant quon na pas de pipe on avance
			si | pipe, pipe

	quand est ce que je check les ./ ???


