
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

t_pipe	*redir_fd_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes)
{
	printf("fd to fd\n");
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
	printf("pipe to pipe\n");
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

int	set_redir(t_cmd *cmd, t_list *l)
{
	t_files	*f;
	int		fail_open;
	bool	prev_in = false;
	bool 	prev_out = false;

	fail_open = 0;
	if (!l)
		return (0);
	f = (t_files *)l->content;
	while (l)
	{
		if (fail_open != 1)
		{
			if (f->filetype == file_from || f->filetype == heredoc_)
			{
				cmd->input = file_from;
				if (prev_in)
					close(cmd->fd_in);
				if (access(f->filename, F_OK) == -1)
				{
					cmd->fd_in = -1;
					ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, f->filename); //1
					fail_open = 1;
				}
				else if (cmd->fd_in != -2)
				{
					cmd->fd_in = open(f->filename, O_RDONLY);
					if (cmd->fd_in == -1)
						ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename); //1
					prev_in = true;
				}
			}
			else if (f->filetype == file_to)
			{
				cmd->output = file_to;
				if (prev_out)
				close (cmd->fd_out);
				cmd->fd_out = open(f->filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
				if (cmd->fd_out == -1)
				{
					ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename); //1
					cmd->fd_out = -1;
				}
				prev_out = true;
			}
			else if (f->filetype == append_)
			{
				cmd->output = file_to;
				if (prev_out)
				close (cmd->fd_out);
				cmd->fd_out = open(f->filename, O_CREAT | O_APPEND | O_RDWR, 0666);
				if (cmd->fd_out == -1)
				{
					ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename);
					cmd->fd_out = -1;
				}
				prev_out = true;
			}
			else if (f->filetype == ambiguous_in)
			{
				if (prev_in)
					close (cmd->fd_in);
				cmd->fd_in = -1;
				ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
				return (1);
			}
			else if (f->filetype == ambiguous_out)
			{
				if (prev_out)
					close (cmd->fd_out);
				cmd->fd_out = -1;
				ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
				return (1);
			}
			else if (f->filetype == pipe_in_)
				cmd->input = pipe_in_;
			else if (f->filetype == pipe_out_)
				cmd->output = pipe_out_;
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
	if (set_redir(cmd, cmd->list_files) == 1)
		return (g_glb = 999, pipes);
	if (cmd->input == stdin_ && cmd->output == stdout_)
		return (pipes);
	if (cmd->fd_in == -2)
		return (data->exec_val = 130, cmd->cmd_type = no_cmd, NULL);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (cmd->cmd_type = no_cmd, NULL);
	if (cmd->input == pipe_in_ || cmd->output == pipe_out_)
	{
		if (cmd->input == pipe_in_ && cmd->output != pipe_out_)
			return (redir_pipe_to_fd(data, cmd ,pipes));
		if (cmd->input != pipe_in_ && cmd->output == pipe_out_)
			return (redir_fd_to_pipe(data, cmd, pipes));
		return (redir_pipe_to_pipe(data, pipes));
	}
	return (redir_fd_to_fd(data, cmd, pipes));
}
