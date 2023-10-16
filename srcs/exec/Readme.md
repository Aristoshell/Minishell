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

- norme
Fait mardi :

-	Point parsing et exec

Fait mercredi :

-	Code du builtin exit (quelques details a regler) 

-	Modification des fonctions d'executions pour acceuillir les builtins

-	Preparation d'un nouveau Main qui permet de passer une deux ou trois commande

Fait Jeudi :

-	terminer exit (ajouter le modulo 256 a la valeur passer en 
parametre)

-	terminer le main (fonction de recup des commandes)

-	correction d'une erreur dans l'exec qui faisait qu'on executais deux 	fois les builtins lorsqu'il y avais des pipes

-	coder echo

-	coder pwd

Vendredi + WE
	- cd work in progress


Mercredi :

-	definition des endroits ou il faut free close et modif le int de $? (dans le child)

-	point avec Marine

-	ajout du int pour $?

-	comprehension sur les signaux 

Jeudi :

-	continuer cd stop car chose a modif apres merge

Vendredi 

-	Merge


A faire

- terminer cd (3/4h)
	- Pourquoi les statics 
	- gestion erreur
	- 

- coder les 4 types de signaux possible et les tester (1/2h)

Bien sûr, voici le code précédent traduit en pseudo-code :

```plaintext
Structure t_envlist:
    Clé (key)
    Valeur (val)
    Drapeau (flag)
    Indice (index)
    Pointeur vers le prochain élément (next)

Fonction de comparaison compareNodes(node1, node2):
    Si node1.key < node2.key OU (node1.key == node2.key ET node1.val < node2.val) Alors
        Retourner un nombre négatif
    Sinon Si node1.key == node2.key ET node1.val == node2.val Alors
        Retourner 0
    Sinon
        Retourner un nombre positif

Fonction de tri sortLinkedList(head):
    Si head est NULL OU head.next est NULL Alors
        Retourner head  # La liste est déjà triée
    Fin Si

    middle = head
    fast = head.next
    Tant que fast n'est pas NULL Faire
        fast = fast.next
        Si fast n'est pas NULL Alors
            fast = fast.next
            middle = middle.next
        Fin Si
    Fin Tant Que

    secondHalf = middle.next
    middle.next = NULL

    sortedFirstHalf = sortLinkedList(head)
    sortedSecondHalf = sortLinkedList(secondHalf)

    Retourner merge(sortedFirstHalf, sortedSecondHalf)

Fonction de fusion merge(list1, list2):
    Si list1 est NULL Alors
        Retourner list2
    Sinon Si list2 est NULL Alors
        Retourner list1
    Sinon Si compareNodes(list1, list2) <= 0 Alors
        list1.next = merge(list1.next, list2)
        Retourner list1
    Sinon
        list2.next = merge(list1, list2.next)
        Retourner list2
    Fin Si

Fonction d'affichage printList(head):
    Tant que head n'est pas NULL Faire
        Afficher "Index: ", head.index, ", Key: ", head.key, ", Val: ", head.val, ", Flag: ", head.flag
        head = head.next
    Fin Tant Que

Fonction principale main():
    # Créez et peuplez votre liste chaînée ici...

    # Triez la liste
    sortedList = sortLinkedList(head)

    printList(sortedList)

    # N'oubliez pas de libérer la mémoire de la liste triée si nécessaire
```

Ce pseudo-code reflète l'algorithme précédent en utilisant des termes généraux, mais il conserve la structure et la logique de tri de la liste chaînée en fonction des critères clé et valeur, tout en attribuant des indices pour correspondre à la position finale dans la liste triée.