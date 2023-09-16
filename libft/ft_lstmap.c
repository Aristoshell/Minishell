/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:29:15 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/14 09:21:46 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: L’adresse du pointeur vers un élément.
f: L’adresse de la fonction à appliquer.
del: L’adresse de la fonction permettant de
supprimer le contenu d’un élément.

Itère sur la liste ’lst’ et applique la fonction
’f ’au contenu de chaque élément. Crée une nouvelle
liste résultant des applications successives de
’f’. La fonction ’del’ est là pour détruire le
contenu d’un élément si nécessaire.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*final;
	t_list	*first;

	if (!del || !lst || !f)
		return (NULL);
	final = ft_lstnew(f(lst->content));
	first = final;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		while (final->next)
			final = final->next;
		final->next = new;
		final = first;
		lst = lst->next;
	}
	return (final);
}
