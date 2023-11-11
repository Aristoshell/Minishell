
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

int	choose_redir(t_cmd *cmd, t_files *f, int *fail_open)
{
	if (f->filetype == file_from || f->filetype == heredoc_)
		return (redir_from(cmd, f, fail_open), 0);
	else if (f->filetype == file_to)
		return (redir_to(cmd, f), 0);
	else if (f->filetype == append_)
		return (redir_append(cmd, f), 0);
	else if (f->filetype == ambiguous_in)
		return (redir_ambigous_in(cmd, f));
	else if (f->filetype == ambiguous_out)
		return (redir_ambigous_out(cmd, f));
	else if (f->filetype == pipe_in_ || f->filetype == pipe_out_)
		cmd->input = f->filetype;
	return (0);
}

int	set_redir(t_cmd *cmd, t_list *l)
{
	t_files	*f;
	int		fail_open;

	fail_open = 0;
	if (l)
		f = (t_files *)l->content;
	while (l && fail_open != 1)
	{
		if (choose_redir(cmd, f, &fail_open))
			return (1);
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
		return (g_glb = ERROR_REDIR, pipes);
	if (cmd->input == stdin_ && cmd->output == stdout_)
		return (pipes);
	if (cmd->fd_in == -2)
		return (data->exec_val = 130, cmd->cmd_type = no_cmd, NULL);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (cmd->cmd_type = no_cmd, NULL);
	if (cmd->input == pipe_in_ || cmd->output == pipe_out_)
	{
		if (cmd->input == pipe_in_ && cmd->output != pipe_out_)
			return (redir_pipe_to_fd(data, cmd, pipes));
		if (cmd->input != pipe_in_ && cmd->output == pipe_out_)
			return (redir_fd_to_pipe(data, cmd, pipes));
		return (redir_pipe_to_pipe(data, pipes));
	}
	return (redir_fd_to_fd(data, cmd, pipes));
}
