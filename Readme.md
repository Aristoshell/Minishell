Pour exec :

-	plusieurs arg sous cette forme ```arg1 "I" arg2 "I" arg3 ```

Fait samedi :

- re creation des arguments en tableau de liste

- re codage d'une fonction strcat pour les args

- readaptation du code pour le tableau de liste et non liste chainee
- recoder les childs pipex

- struct des pipes et modification de ces derniers entre chaque appel de child

Fait lundi :

- creer un systeme agile pour les redirections
	-idee : au lieu de faire 3 childs distinct redirige en fonction des sorties 
	- 4 possibilite : fd_in et fd_out
					  pipe_in et fd_out
					  pipe_in et pipe_out
					  fd_in et pipe_out

- prise en compte des builtins

- update commentaire

- rangement des fonctions dans un systeme de fichier logique et bien organise

- free + close tout les pipes et fd dans le cas ou tout est ok

A faire :

- free + close tout les pipes et fd dans les cas d'erreur
- retour du $?
- norme
- signaux ?