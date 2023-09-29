/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_envlist_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

// void	ft_clean_t_envlist_node(t_envlist *env)
// {
// 	if (!env)
// 		return ;
// 	ft_clean_string((char*)env->key);
// 	ft_clean_string(env->val);
// 	env->flag = 0;
// 	env->next = NULL;
// 	free(env);
// 	env = NULL;
// }

/* On l'enlevera par la suite i guess*/
void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	free((void *)lst->key);
	lst->key = NULL;
	//ft_bzero(lst->val, ft_strlen(lst->val));
	free(lst->val);
	lst->val = NULL;
	lst->flag = 0;
	free(lst);
	lst = NULL;
}

