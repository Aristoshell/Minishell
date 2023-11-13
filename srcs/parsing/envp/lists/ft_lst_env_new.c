/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:43 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:44 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_lst_env_new(const char *key, char *val)
{
	t_envlist	*newlist;

	newlist = malloc(sizeof(t_envlist));
	if (newlist == NULL)
		return (MEMORY_ERROR_PT);
	newlist->key = key;
	if (val)
		newlist->val = val;
	else
		newlist->val = NULL;
	newlist->flag = 0;
	ft_set_flag(&newlist->flag, val);
	newlist->next = NULL;
	return (newlist);
}
