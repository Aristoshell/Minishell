
#include "minishell.h"
#include "minishell_louis.h"


void	close_and_free(t_pipe *pipes, int stdin_save, int stdout_save, int status)
{
	if (status > 0)
		free(pipes);
	close(stdin_save);
	close(stdout_save);
}
void	pipe_error(t_data *data, t_pipe *pipes)
{
	close(data->stdin_save);
	close(data->stdout_save);
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	exit(99);
}

void	close_pipes(t_data *data, t_pipe *pipes)
{
	if (pipes)
	{
		if (data->nb_command > 1)
		{
			if (pipes->tube[0][0] != -1)
				close(pipes->tube[0][0]);
			if (pipes->tube[0][1] != -1)
			close(pipes->tube[0][1]);
		}
		if (pipes->tube[1][0] != -1)
			close(pipes->tube[1][0]);
		if (pipes->tube[1][1] != -1)
			close(pipes->tube[1][1]);
	free(pipes);
	}

}

void	close_fd(t_cmd **cmd, int len_list,
	int stdin_save, int stdout_save)
{
	int	i;

	i = 0;
	while (i < len_list)
	{
		if (cmd[i]->input != pipe_in_)
			dup2(stdin_save, 0);
		if (cmd[i]->output != pipe_out_)
			dup2(stdout_save, 1);
		i++;
	}
	close(stdin_save);
	close(stdout_save);
}
