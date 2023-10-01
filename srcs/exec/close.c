
#include "minishell.h"
#include "minishell_louis.h"


void	close_pipes(t_pipe *pipes)
{
	close(pipes->tube[0][0]);
	close(pipes->tube[0][1]);
	close(pipes->tube[1][0]);
	close(pipes->tube[1][1]);
}

void	close_list_args(t_cmd **cmd, int len_list, int stdin_, int stdout_)
{
	int	i;

	i = 0;
	while (i < len_list)
	{
		close(cmd[i]->input);
		close(cmd[i]->output);
		dup2(stdin_, 0);
		dup2(stdout_, 1);
		i++;
	}
}
