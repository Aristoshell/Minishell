/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_delone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:35 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:37 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	free((void *)lst->key);
	lst->key = NULL;
	if (lst->val)
	{
		free(lst->val);
		lst->val = NULL;
	}
	lst->flag = 0;
	free(lst);
	lst = NULL;
}
