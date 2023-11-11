/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 00:30:30 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	unlink_files(t_list *l)
{
	t_files	*f;

	if (!l)
		return ;
	f = (t_files *)l->content;
	while (l)
	{
		if (f->filetype == heredoc_)
			unlink(f->filename);
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
}

void	close_files(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_command)
	{
		if (data->cmd[i]->input == file_from
			&& data->cmd[i]->fd_in != -1 && data->cmd[i]->fd_in != -2)
			close(data->cmd[i]->fd_in);
		if (data->cmd[i]->output == file_to
			&& data->cmd[i]->fd_out != -1 && data->cmd[i]->fd_out != -2)
			close(data->cmd[i]->fd_out);
		unlink_files(data->cmd[i]->list_files);
		i++;
	}
}
