/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:28:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/17 12:10:01 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

// la fonction va pas car je dois checker si la variable existe pas deja et aussi changer ses settings,
// si "export OMG" mais que omg existe deja et quon lui reassigne aucune valeur, on necrase pas sa valeur
// si "export OMG=" la on met aucune valeur (mais elle reste dans lenv, parce que ca va juste bzero mon char * ou malloc size of char  *1 = \0)
// penser a bien checker les flags
// attention !!!! je peux donner plusieurs arg a export ; ex = export hihi bla blu

int	export(t_envlist **env, char *line)
{
	t_envlist	*new;

	printf("%s\n",line);
	new = ft_new_envvar(line);
	if (!new)
		return (-1);
	if (!(*env))
		*env = new;
	while ((*env))
	{
		if (strcmp((*env)->key, new->key) == 0)
		{
			if (new->val != NULL)
			{
				ft_lst_env_delone(*env);
				ft_lst_env_add_back(env, new);
			}
		}
		(*env) = (*env)->next;
	}
	return (0);
}


int compareNodes(const t_envlist *node1, const t_envlist *node2)
{
    int keyComparison = strcmp(node1->key, node2->key);
    if (keyComparison != 0)
        return keyComparison;
    return strcmp(node1->val, node2->val);
}

// Function to print the sorted list
void printlist(t_envlist *node) 
{
	while (node != NULL) {
		printf("Key: %s, Val: %s, Flag: %d\n", node->key, node->val, node->flag);
		node = node->next;
	}
}

void	sort_list(t_envlist *env)
{
	//t_envlist *sorted_list;
	
	while (env != NULL)
	{
		printf("%s\n", env->key);
		env = env->next;
		//printf("%s\n", to_comp->key);
	}
}


void	display_export(t_envlist *env)
{
	//t_envlist sorted_list;

	/*sorted_list = */sort_list(env);
	//printlist(env);
	while (env)
	{
		if (MASK_EXPORT & env->flag)
			ft_dprintf(STDOUT_FILENO, "export %s\"=%s\"\n", env->key, env->val);
		env = env->next;
	}
}

// export qq chose
// avec val ou pas
