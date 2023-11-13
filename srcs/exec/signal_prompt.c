/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:41:06 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 03:01:49 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler(int signum)
{
	(void)signum;
	if (isatty(STDOUT_FILENO))
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	g_glb = 130;
	return ;
}

void	handle_signals_prompt(t_data *data)
{
	if (g_glb == 130)
		data->exec_val = 130;
	g_glb = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
}
