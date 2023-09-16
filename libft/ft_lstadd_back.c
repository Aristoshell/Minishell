/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:25:28 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/11 16:45:13 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: L’adresse du pointeur vers le premier élément
de la liste.
new: L’adresse du pointeur vers l’élément à
rajouter à la liste.

Ajoute l’élément ’new’ à la fin de la liste.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst)
	{
		if (*lst)
		{
			end = ft_lstlast(*lst);
			end->next = new;
		}
		else
			*lst = new;
	}
}
