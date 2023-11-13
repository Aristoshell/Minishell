/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:12 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:13 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_new_envvar(char *line)
{
	const int	sep = ft_strchr_int(line, '=');
	const char	*key = ft_get_key(line, sep);
	char		*val;
	t_envlist	*node;

	node = NULL;
	if (!key)
		return (MEMORY_ERROR_PT);
	if (sep < 0)
		val = NULL;
	else
	{
		val = ft_get_val(&line[sep + 1]);
		if (!val)
			return (free((char *)key), key = NULL, MEMORY_ERROR_PT);
	}
	node = ft_lst_env_new(key, val);
	if (!node)
	{
		if (val)
			free(val);
		return (free((char *)key), key = NULL, val = NULL, MEMORY_ERROR_PT);
	}
	return (node);
}
