/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/19 17:05:21 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	g_glb = 130;
	return ;
}

void    handle_signals_heredoc()
{
	signal(SIGINT, &sighandler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler(int signum)
{
	(void)signum;
	if (isatty(STDOUT_FILENO))
	{
		printf("\n");
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	g_glb = 1;
	return ;
}

void    handle_signals_prompt()
{
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
}
