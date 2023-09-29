/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:24:31 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/10 19:47:59 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: Le début de la liste.

Renvoie le dernier élément de la liste.
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*actual;

	if (lst == 0)
		return (lst);
	actual = lst;
	while (actual->next)
		actual = actual->next;
	return (actual);
}
