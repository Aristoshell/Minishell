/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:47:47 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*ft_new_envvar(char *line)
{
	const int	sep = ft_strchr_int(line, '=');
	const char	*key = get_key(line, sep);
	char		*val;
	t_envlist	*node;

	node = NULL;
	if (!key)
		return (NULL); // attention, secu
	if (sep < 0)
		val = NULL;
	else
	{
		val = get_val(&line[sep + 1]);
		if (!val)
			return (NULL);
		node = ft_lst_env_new(key, val);
		if (!node)
			return (NULL);//penser a bien clean
	}
	return (node);
}
