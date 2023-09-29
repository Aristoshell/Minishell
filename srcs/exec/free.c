
#include "minishell.h"
#include "minishell_louis.h"


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
