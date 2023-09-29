/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_add_front.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:49:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_env_add_front(t_envlist **lst, t_envlist *new)
{
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			new->next = (*lst);
		}
		*lst = new;
	}
}
