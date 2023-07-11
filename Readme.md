

faire un make re

ensuite ecrire n'importe quelle commande avec ses arguments.

Sous cette forme 

./Exec_Minishell cmd1 "|" cmd 2 
(les deux childs se lancerons mais ne communiquent pas correctement atm)
(ls ls fonctionne)

Le pipe doit etre entre quote sinon il sera interprete comme un vrai pipe

tu peux t'amuser a changer les type des input et output dans le main afin de tester les redirections de fichier a fichier

actuelement ils sont sous la forme 
cmd 1 : input = file in / output pipe
cmd 2 : input pipe / output file out

Rien ne fonctionne vraiment mais je suis claque je vais rentrer 