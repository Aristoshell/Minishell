/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:04:00 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 21:07:34 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_redir	redir_from_heredoc(t_files *f, t_cmd *cmd, t_redir r)
{
	cmd->input = file_from;
	if (cmd->fd_in == -1)
	{
		cmd->fd_in = -1;
		ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, f->filename);
		r.fail_open = 1;
	}
	return (r);
}

t_redir	redir_from_file(t_files *f, t_cmd *cmd, t_redir r)
{
	cmd->input = file_from;
	if (r.prev_in == true)
		close(cmd->fd_in);
	cmd->fd_in = open(f->filename, O_RDONLY);
	if (access(f->filename, F_OK) == -1)
	{
		cmd->fd_in = -1;
		ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, f->filename);
		r.fail_open = 1;
	}
	else if (access(f->filename, R_OK == -1) || cmd->fd_in == -1)
	{
		cmd->fd_in = -1;
		ft_dprintf(STDERR_FILENO, D_ER_PERM, f->filename);
		r.fail_open = 1;
	}
	if (r.fail_open != 1)
		r.prev_in = true;
	return (r);
}