/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:20:58 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/14 13:15:44 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_redir	redir_file_from(t_files *f, t_cmd *cmd, t_redir r)
{
	if (f->filetype == heredoc_)
		r = redir_from_heredoc(f, cmd, r);
	else
		r = redir_from_file(f, cmd, r);
	return (r);
}

t_redir	redir_file_to(t_files *f, t_cmd *cmd, t_redir r)
{
	cmd->output = file_to;
	if (r.prev_out)
		close (cmd->fd_out);
	cmd->fd_out = open(f->filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->fd_out == -1)
	{
		r.fail_open = 1;
		ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename);
		cmd->fd_out = -1;
	}
	r.prev_out = true;
	return (r);
}

t_redir	redir_append(t_files *f, t_cmd *cmd, t_redir r)
{
	cmd->output = file_to;
	if (r.prev_out)
		close (cmd->fd_out);
	cmd->fd_out = open(f->filename, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->fd_out == -1)
	{
		r.fail_open = 1;
		ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename);
		cmd->fd_out = -1;
	}
	r.prev_out = true;
	return (r);
}

void	redir_ambigous_in(t_files *f, t_cmd *cmd, t_redir r)
{
	if (r.prev_in)
		close (cmd->fd_in);
	cmd->fd_in = -1;
	ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
}

void	redir_ambigous_out(t_files *f, t_cmd *cmd, t_redir r)
{
	if (r.prev_out)
		close (cmd->fd_out);
	cmd->fd_out = -1;
	ft_dprintf(STDERR_FILENO, D_ER_AMB, f->filename);
}
