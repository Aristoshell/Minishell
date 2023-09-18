/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/18 22:50:50 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(char *line)
{
	char	*val;
	int		size;

	size = ft_strlen(line);
	val = malloc((size + 1) * sizeof(char));
	if (!val)
		return (NULL);// attention a l'erreur renvoyee
	ft_strlcpy(val, line, (size + 1));
	return (val);
}

char	*get_key(char *line, int sep)
{
	char	*key;
	int		size;
	
	if (sep < 0)
		size = ft_strlen(line);
	else
		size = sep;
	key = malloc((size + 1) * sizeof(char));
	if (!key)
		return (NULL);// attention a l'erreur renvoyee
	ft_strlcpy(key, line, (size + 1));
	return (key);
}

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
		val = get_val(&line[sep+1]);
		if (!val)
			return (NULL);
		node = ft_lst_env_new(key, val);
		if (!node)
			return (NULL);//penser a bien clean
	}
	return (node);
}

void	print_env(t_envlist *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}

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
	print_env(list);
	ft_lst_pop(&list, NULL);
	printf("\n\n\n");
	print_env(list);
	return (list);	
}
