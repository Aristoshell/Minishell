/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:39:48 by madavid           #+#    #+#             */
/*   Updated: 2022/12/14 17:54:07 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
