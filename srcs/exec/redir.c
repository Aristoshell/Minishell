/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:04:48 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 21:21:16 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_redir	select_redir(t_files *f, t_cmd *cmd, t_redir r)
{
	if (f->filetype == file_from || f->filetype == heredoc_)
		r = redir_file_from(f, cmd, r);
	else if (f->filetype == file_to)
		r = redir_file_to(f, cmd, r);
	else if (f->filetype == append_)
		r = redir_append(f, cmd, r);
	else if (f->filetype == ambiguous_in)
		return (redir_ambigous_in(f, cmd, r), r.fail_open = -1, r);
	else if (f->filetype == ambiguous_out)
		return (redir_ambigous_out(f, cmd, r), r.fail_open = -1, r);
	else if (f->filetype == pipe_in_)
		cmd->input = pipe_in_;
	else if (f->filetype == pipe_out_)
		cmd->output = pipe_out_;
	return (r);
}

int	set_redir(t_cmd *cmd, t_list *l)
{
	t_files	*f;
	t_redir	r;

	r.fail_open = 0;
	if (!l)
		return (0);
	f = (t_files *)l->content;
	while (l)
	{
		if (r.fail_open != 1 && r.fail_open != -1)
		{
			r = select_redir(f, cmd, r);
			if (r.fail_open == -1)
				return (1);
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
			return (redir_pipe_to_fd(data, cmd, pipes));
		if (cmd->input != pipe_in_ && cmd->output == pipe_out_)
			return (redir_fd_to_pipe(data, cmd, pipes));
		return (redir_pipe_to_pipe(data, pipes));
	}
	return (redir_fd_to_fd(data, cmd, pipes));
}
