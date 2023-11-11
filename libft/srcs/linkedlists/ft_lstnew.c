/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:36:21 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:36:23 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

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
