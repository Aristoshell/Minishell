# Minishell

Notes 06/07/2023 :

Executable : minishell

Utilisation : 

- lancer le programme avec ./minishell
- écrire dans le prompt, le prompt va répondre "t'as dit : [input]" afin de répéter ce qui a été dit
- le reader va checker le cas de quotes non fermées et faire en sorte de les fermer (déjà testé avec pas mal de combinaisons)

**Built-in**
22/07 : 
- echo et echo -n fait (vérifs à faire + sûrement à adapter un peu pour l'exec)
- cd en cours
- pwd en cours
--> les deux ne marchent pas, je les reprendrait plus tard

**Prompt**

Un prompt avec historique fonctionnel

Gestion des quotes :
- normalement ça marche, j'ai bien testé plusieurs cas, 
- besoin de checker les leaks
- besoin de checker les retours de malloc
- besoin de raccourcir les fonctions et sortir le gros bloc de check de quote de la fonction prompt pour alléger


**Lexer**

Un lexer qui décompose la ligne lue sous forme de liste chainée et précise si word ou token 

Besoin de :
- double chainer la liste
- checker l'histoire des quotes

Problème possible : 
- on fait un split avec des espaces, mais si j'ai un "echo coucou|ls", les mots ne vont pas être séparés mais pourtant dans le shell ils devraient
- or si j'utilise mes tokens en séparateur, je ne suis pas à l'abris d'avoir un token dans une quote qui ne devrait pas être séparé....


**Parser**

Regrouper les mots et les tokens en paquet pour fournir à Louis ce dont il a besoin




**Parsing**

Etape 1 : reader
- Va donner une grande chaine de charactere

Etape 2 : lexer
- va separer chaque mot un a un en indiquant son token
- utiliser un enum pour check si on est dans une quote ou pas
- format liste chainee

Etape 3 : parser
- va creer un maillon par commande en incluant ses redirections




--> split sur l'espace qui renvoie un tab de char *
--> parcours le tab de char avec double boucle
