
#include "minishell.h"
#include "minishell_louis.h"


/*
sert a faire nos redirection au debut du child
il y a 4 possibilites 

-> on a au moins un pipe
	-> si il est en entre
	-> si il est en sortie
	-> il est en entree et en sortie
-> on a pas de pipe

on s'occuperas de modifier la sortie standard et 
l'entree standard dans tout les cas possible
grace a dup2 exactement comme on le fait dans split
*/

t_pipe	*redir_fd_to_fd(t_cmd *cmd, t_pipe *pipes)
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
	return (pipes);
}

t_pipe	*redir_pipe_to_pipe(t_pipe *pipes)
{

	if (dup2(pipes->tube[0][0], 0) == -1 \
		|| dup2(pipes->tube[1][1], 1) == -1)
		error_dup2();
	close (pipes->tube[0][1]);
	close (pipes->tube[1][0]);
	return (pipes);
}

t_pipe	*redir_pipe_to_fd(t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->output != stdout_)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			error_dup2();
	}
	if (dup2(pipes->tube[0][0], 0) == -1)
	{
		printf("1\n");
		error_dup2();
	}
	close(pipes->tube[0][1]);
	return (pipes);
}

t_pipe	*redir_fd_to_pipe(t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->input != stdin_)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			error_dup2();
	}
	if (dup2(pipes->tube[1][1], 1) == -1)
	{
		printf("1\n");
		error_dup2();
	}
	close(pipes->tube[1][0]);
	return (pipes);
}

t_pipe	*handle_redirection(t_data *data, t_pipe *pipes)
{
	t_cmd	*cmd;

	cmd = data->cmd[data->current_cmd];
	if(cmd->input == stdin_ && cmd->output == stdout_)
		return (pipes);
	else if (cmd->input == file_ || cmd->output == file_)
		printf("open file\n");
	if (cmd->input == pipe_ || cmd->output == pipe_)
	{
		if (cmd->input == pipe_ && cmd->output != pipe_)
			return (redir_pipe_to_fd(cmd ,pipes));
		if (cmd->input != pipe_ && cmd->output == pipe_)
			return (redir_fd_to_pipe(cmd, pipes));
		return (redir_pipe_to_pipe(pipes));
	}
	return (redir_fd_to_fd(cmd, pipes));
}
