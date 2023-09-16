/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:24:07 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/17 15:01:43 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: L’élément à free
del: L’adresse de la fonction permettant de
supprimer le contenu de l’élément.

Libère la mémoire de l’élément passé en argument en
utilisant la fonction ’del’ puis avec free(3). La
mémoire de ’next’ ne doit pas être free.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
