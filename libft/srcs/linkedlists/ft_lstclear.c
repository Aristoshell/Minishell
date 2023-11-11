/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:36:07 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:36:08 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

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
