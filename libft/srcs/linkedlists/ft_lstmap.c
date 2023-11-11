/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:36:19 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:36:20 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*anne;
	t_list	*marc;

	anne = NULL;
	while (lst != NULL)
	{
		marc = ft_lstnew(f(lst->content));
		if (!marc)
		{
			ft_lstclear(&anne, del);
			return (NULL);
		}
		ft_lstadd_back(&anne, marc);
		lst = lst->next;
	}
	return (anne);
}
