#include "minishell.h"
#include "minishell_louis.h"

t_pipe	*redir_fd_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->input != stdin_)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			error_dup2();
	}
	if (cmd->output != stdout_)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			error_dup2();
	}
	close_pipes(data, pipes);
	return (pipes);
}

t_pipe	*redir_pipe_to_pipe(t_data *data, t_pipe *pipes)
{
	if (dup2(pipes->tube[0][0], 0) == -1 \
		|| dup2(pipes->tube[1][1], 1) == -1)
		error_dup2();
	close_pipes(data, pipes);
	return (pipes);
}

t_pipe	*redir_pipe_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->output != stdout_)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			error_dup2();
	}
	if (dup2(pipes->tube[0][0], 0) == -1)
		error_dup2();
	close_pipes(data, pipes);
	return (pipes);
}

t_pipe	*redir_fd_to_pipe(t_data *data, t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->input != stdin_)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			error_dup2();
	}
	if (dup2(pipes->tube[1][1], 1) == -1)
		error_dup2();
	close_pipes(data, pipes);
	return (pipes);
}
