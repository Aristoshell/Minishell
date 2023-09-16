/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:23:25 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/14 09:22:06 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: Le début de la liste.

Compte le nombre d’éléments de la liste.
*/

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*actual;

	i = 0;
	actual = lst;
	while (actual)
	{
		actual = actual->next;
		i++;
	}
	return (i);
}
