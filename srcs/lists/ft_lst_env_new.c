/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 19:01:40 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	set_flag(&newlist->flag, val);
	newlist->next = NULL;
	return (newlist);
}
