/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:56:25 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/16 15:52:19 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_get_size_export(t_envlist *env)
{
	int	size;

	size = 0;
	while (env)
	{
		if (MASK_EXPORT & env->flag)
			size++;
		env = env->next;
	}
	return (size);
}

void	ft_del_sorted_export(char ***tab, int size)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < size)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
}

char	***ft_get_copy_export(t_envlist *env, int size)
{
	char	***copy_export;
	int		i;

	copy_export = (char ***)malloc(size * sizeof(char **));
	i = 0;
	if (!copy_export)
		return (MEMORY_ERROR_PT);
	while (env)
	{
		if (MASK_EXPORT & env->flag)
		{
			copy_export[i] = (char **)malloc(size * sizeof(char *));
			if (!copy_export[i])
			{
				ft_del_sorted_export(copy_export, size);
				return (MEMORY_ERROR_PT);
			}
			copy_export[i][0] = (char *)env->key;
			copy_export[i][1] = env->val;
			i++;
		}
		env = env->next;
	}
	return (copy_export);
}

int	display_messages(char ***tab, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (tab[i][1])
		{
			if (ft_dprintf(1, "export %s=\"%s\"\n", tab[i][0], tab[i][1]) == -1)
				return (exp_err(), ft_del_sorted_export(tab, size), 1);
		}
		else
		{
			if (ft_dprintf(1, "export %s\n", tab[i][0]) == -1)
				return (exp_err(), ft_del_sorted_export(tab, size), 1);
		}
		i++;
	}
	return (ft_del_sorted_export(tab, size), FUNCTION_SUCCESS);
}

int	display_export(t_envlist *env, char **args)
{
	int		size;
	char	***tab;

	if (args[1])
	{
		ft_dprintf(2, D_ER_EXPORT_UNSET, "export", args[1][0], args[1][1]);
		return (2);
	}
	size = ft_get_size_export(env);
	tab = ft_get_copy_export(env, size);
	if (!tab)
		return (MEMORY_ERR_NB);
	ft_quick_sort(tab, 0, size - 1);
	return (display_messages(tab, size));
}
