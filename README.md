# Minishell

Notes 06/07/2023 :

Executable : minishell

**Built-in**
22/07 : 
- echo et echo -n fait (vérifs à faire + sûrement à adapter un peu pour l'exec)
- cd en cours
- pwd en cours

**Prompt**

Un prompt avec historique fonctionnel

Besoin de : 
- checker les leaks


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