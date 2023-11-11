/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:36:04 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:36:05 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			new->next = (*lst);
		}
		*lst = new;
	}
}
