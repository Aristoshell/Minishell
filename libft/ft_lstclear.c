/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:26:43 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/15 21:40:19 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: L’adresse du pointeur vers un élément.
del: L’adresse de la fonction permettant de
supprimer le contenu d’un élément.

Supprime et libère la mémoire de l’élément passé en
paramètre, et de tous les éléments qui suivent, à
l’aide de ’del’ et de free(3)
Enfin, le pointeur initial doit être mis à NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_to_del;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		next_to_del = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_to_del;
	}
}
