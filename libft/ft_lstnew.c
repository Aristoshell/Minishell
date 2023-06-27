/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2022/12/18 13:17:29 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *contenu)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	newlist->content = contenu;
	newlist->next = NULL;
	return (newlist);
}
