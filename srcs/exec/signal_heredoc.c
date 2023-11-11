/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:41:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 16:47:01 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_heredoc(int sig)
{
	int	fd;

	(void)sig;
	fd = open ("/dev/null", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	printf("\n");
	g_glb = 130;
	return ;
}

void	handle_signals_heredoc(t_data *data)
{
	if (g_glb == 130)
		data->exec_val = 130;
	g_glb = 0;
	signal(SIGINT, sighandler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
