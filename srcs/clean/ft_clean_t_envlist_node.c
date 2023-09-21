/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_envlist_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 02:12:45 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_t_envlist_node(t_envlist *env)
{
	if (!env)
		return ;
	ft_clean_string(env->key);
	ft_clean_string(env->val);
	env->flag = 0;
	env->next = NULL;
	free(env);
	env = NULL;
}

/*
void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	ft_bzero((void *)lst->key, ft_strlen(lst->key));
	free((void *)lst->key);
	ft_bzero(lst->val, ft_strlen(lst->val));
	free(lst->val);
	lst->flag = 0;
	free(lst);
}
*/