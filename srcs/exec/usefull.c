
#include "minishell.h"
#include "minishell_louis.h"


/*
retourne la taille du tableau de liste
*/

int	strlen_list(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (-1);
	while (cmd[i])
		i++;
	return (i);
}

char	**list_to_array(t_envlist *list)
{
	int	i;
	int j;
	char **ret;

	i = ft_envlstsize(list);
	ret = ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if (list->flag == MASK_ENV)
		{
			ret[j] = join_lign_env(list);
			j++;
		}
		list = list->next;
	}
	ret[j] = NULL;
	return (ret);
}

void	free_list_args(t_cmd **cmd, t_pipe *pipes, int len_list)
{
	int	i;
	int	j;

	i = 0;
	while (i < len_list)
	{
		j = 0;
		while (cmd[i]->cmd_args[j])
		{
			free(cmd[i]->cmd_args[j]);
			j++;
		}
		free(cmd[i]->cmd_args);
		free(cmd[i]);
		i++;
	}
	if (len_list > 1)
		free(pipes);
}
