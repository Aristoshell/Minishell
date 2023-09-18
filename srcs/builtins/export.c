/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:25 by madavid           #+#    #+#             */
/*   Updated: 2023/09/18 23:12:16 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// la fonction va pas car je dois checker si la variable existe pas deja et aussi changer ses settings, 
// si "export OMG" mais que omg existe deja et quon lui reassigne aucune valeur, on necrase pas sa valeur
// si "export OMG=" la on met aucune valeur (mais elle reste dans lenv)
int	export(t_envlist **env, char *line)
{
	t_envlist	*new; 

	new = ft_new_envvar(line);
	if (!new)
		return (-1);
	if (!(*env))
		*env = new;
	else
		ft_lst_env_add_back(env, new); // checker si pb ?
	return (0);
}
// il faut add un algo de tri pour le display trie
void	display_export(t_envlist *env)
{
	while (env)
	{
		if (MASK_EXPORT & env->flag) // si different de 0
			ft_dprintf(STDOUT_FILENO ,RED"export %s\"=%s\"\n"NC, env->key, env->val);
		env = env->next;
	}
}

// export qq chose
// avec val ou pas
