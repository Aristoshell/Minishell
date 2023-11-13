/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:36:59 by marine            #+#    #+#             */
/*   Updated: 2023/11/12 20:37:09 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	unset_single(t_envlist **lst, char *key)
{
	t_envlist	*prev;
	t_envlist	*next;
	t_envlist	*curr;

	prev = NULL;
	curr = (*lst);
	next = NULL;
	if (!(*lst) || !key)
		return ;
	while (curr->next && ft_strcmp(key, curr->key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		(*lst) = (*lst)->next;
	else
	{
		if (!curr || ft_strcmp(key, curr->key))
			return ;
		next = curr->next;
	}
	ft_lst_env_delone(curr);
	if (prev)
		prev->next = next;
}

int	unset(t_envlist **env, char **key)
{
	int	i;

	i = 1;
	if (key[i] && key[i][0] == '-')
		return (ft_dprintf(2, D_ER_EXPORT_UNSET, "unset", key[1]), 2);
	while (key[i])
	{
		unset_single(env, key[i]);
		i++;
	}
	return (0);
}
