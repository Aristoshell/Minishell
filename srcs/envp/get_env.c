/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/17 17:27:23 by madavid          ###   ########.fr       */
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
	int			sep;
	char		*val;
	char		*key;
	t_envlist	*node;
	sep = ft_strchr_int(line, '=');
	key = get_key(line, sep);
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
			return (NULL);//bien clean
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

// void	add_new_node(t_envlist **lst, char *var)
// {
// 	t_envlist	*prev;
// 	t_envlist	*next;
// 	t_envlist	*new;

// 	new = ft_new_envvar(var);
// 	// add protection
// 	while ()
// }

t_envlist	*get_envp(char **envp)
{
	int			i;
	t_envlist	*list;

	i = 0;
	list = NULL;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		if (!list)
		{
			list = ft_new_envvar(envp[i]);
			if (!list)
				return (NULL);
		}
		else
		{
			//fonction pour add au bon endroit et je lui envoi envp[i]
			ft_lst_env_add_back(&list, ft_new_envvar(envp[i])); // ya pas de verif
		}
		i++;
	}
	print_env(list);
	return (list);	
}