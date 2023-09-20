/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:46:46 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*get_envp(char **envp)
{
	int			i;
	t_envlist	*list;
	t_envlist	*new;

	i = 0;
	list = NULL;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		new = ft_new_envvar(envp[i]);
		if (!new)
			return (NULL);
		if (!list)
			list = new;
		else
			ft_lst_env_add_back(&list, new);
		i++;
	}
	return (list);
}
