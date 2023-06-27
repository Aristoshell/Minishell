/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:10:25 by madavid           #+#    #+#             */
/*   Updated: 2022/12/18 13:15:20 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (del)(void *))
{
	t_list	*p;

	if (lst && del)
	{
		p = *lst;
		while (*lst)
		{
			p = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = p;
		}
	}
}
