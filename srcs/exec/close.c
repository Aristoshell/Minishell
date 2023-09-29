/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:53:08 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"


void	close_pipes(t_pipe *pipes)
{
	close(pipes->tube[0][0]);
	close(pipes->tube[0][1]);
	close(pipes->tube[1][0]);
	close(pipes->tube[1][1]);
}

void	close_list_args(t_cmd **cmd, int len_list)
{
	int	i;

	i = 0;
	while (i < len_list)
	{
		if (cmd[i]->input == append_ || cmd[i]->input == file_
			|| cmd[i]->input == heredoc_)
			close(cmd[i]->fd_in);
		if (cmd[i]->output == append_ || cmd[i]->output == file_
			|| cmd[i]->output == heredoc_)
			close(cmd[i]->fd_out);
		i++;
	}
}
