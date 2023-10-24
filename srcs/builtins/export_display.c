
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
				return (MEMORY_ERROR_PT); //et d'autres free
			copy_export[i][0] = (char *)env->key;
			copy_export[i][1] = env->val;
			i++;
		}
		env = env->next;
	}
	return (copy_export);
}

void	ft_del_sorted_export(char ***tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
}

int	display_export(t_envlist *env)
{
	int		size;
	char	***tab;
	int		i;

	i = 0;
	size = ft_get_size_export(env);
	tab = ft_get_copy_export(env, size);
	if (!tab)
		return (MEMORY_ERR_NB);
	ft_quick_sort(tab, 0, size - 1);
	while (i < size)
	{
		if (tab[i][1])
			ft_dprintf(STDOUT_FILENO, "export %s=\"%s\"\n", tab[i][0], tab[i][1]);
		else
			ft_dprintf(STDOUT_FILENO, "export %s\n", tab[i][0]);
		i++;
	}
	ft_del_sorted_export(tab, size);
	return (FUNCTION_SUCCESS);
}
