/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_pop(t_envlist **lst, char *key)
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
	if (!prev) // trouve mais premier maillon
		(*lst) = (*lst)->next;
	else // trouve
	{
		if (!curr || ft_strcmp(key, curr->key)) // pas trouve
			return ;
		next = curr->next;
	}
	ft_lst_env_delone(curr);
	if (prev)
		prev->next = next;
}
