/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:21:16 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/14 09:22:25 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: L’adresse du pointeur vers le premier élément
de la liste.
new: L’adresse du pointeur vers l’élément à
rajouter à la liste.

Ajoute l’élément ’new’ au début de la liste.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
