
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
		error_dup2();
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
		error_dup2();
	close(pipes->tube[1][0]);
	return (pipes);
}

int	set_redir(t_cmd *cmd, t_data *data, t_list *l)
{
	t_files	*f;
	int		fail_open;

	if (!data)
		return 0;
	if (!cmd)
		return 0;
	fail_open = 0;
	if (!l)
		return (0);
	f = (t_files *)l->content;
	while (l)
	{
		if (fail_open == 1)
		{
			if (f->filetype == heredoc_)
			{
				cmd->fd_in = heredoc(f->filename, data);
				cmd->input = file_from;
			}
		}
		else
		{
			if (f->filetype == file_from)
			{
				cmd->fd_in = open(f->filename, O_RDONLY);
				cmd->input = file_from;
			}
			else if (f->filetype == file_to)
			{
				cmd->fd_out = open(f->filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
				cmd->output = file_to;
			}
			else if (f->filetype == append_)
			{
				cmd->fd_out = open(f->filename, O_CREAT | O_APPEND | O_RDWR, 0666);
				cmd->fd_out = file_to;
			}
			else if (f->filetype == heredoc_)
			{
				cmd->fd_in = heredoc(f->filename, data);
				cmd->input = file_from;
			}
			else if (f->filetype == pipe_in_)
			{
				cmd->input = pipe_in_;
			}
			else if (f->filetype == pipe_out_)
			{
				cmd->output = pipe_out_;
			}
			else if (cmd->fd_in == -1 || cmd->fd_out == -1)
				fail_open = 1;
		}
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
	return (0);
}

t_pipe	*handle_redirection(t_data *data, t_pipe *pipes)
{
	t_cmd	*cmd;

	cmd = data->cmd[data->current_cmd];
	set_redir(cmd, data, cmd->list_files);
	if (cmd->input == stdin_ && cmd->output == stdout_)
		return (pipes);
	if (cmd->input == pipe_in_ || cmd->output == pipe_out_)
	{
		if (cmd->input == pipe_in_ && cmd->output != pipe_out_)
			return (redir_pipe_to_fd(cmd ,pipes));
		if (cmd->input != pipe_in_ && cmd->output == pipe_out_)
			return (redir_fd_to_pipe(cmd, pipes));
		return (redir_pipe_to_pipe(pipes));
	}
	return (redir_fd_to_fd(cmd, pipes));
}
