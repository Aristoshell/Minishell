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

Besoin de : 
- checker les leaks

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

**Parser**

Regrouper les mots et les tokens en paquet pour fournir à Louis ce dont il a besoin

Besoin de :
- mieux comprendre ce dont Louis a besoin
- y a t'il besoin d'une liste doublement chaînée ?