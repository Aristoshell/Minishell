/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:56 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:56:58 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_get_envp(t_envlist **env, char **envp)
{
	int			i;
	t_envlist	*new;

	i = 0;
	if (!envp || !envp[0])
		return (FUNCTION_SUCCESS);
	while (envp[i])
	{
		new = ft_new_envvar(envp[i]);
		if (!new)
			return (ft_lst_env_clear(env), MEMORY_ERR_NB);
		if (!*env)
			*env = new;
		else
			ft_lst_env_add_back(env, new);
		i++;
	}
	return (FUNCTION_SUCCESS);
}
