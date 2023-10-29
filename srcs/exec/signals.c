/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/29 16:54:41 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_heredoc(int sig)
{
	int fd;

	(void)sig;
	fd = open ("/dev/null", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	printf("\n");
	g_glb = 130;
	return ;
}

void handle_signals_heredoc()
{
	g_glb = 0;
    signal(SIGINT, sighandler_heredoc);
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
	g_glb = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
}


static void    sighandler_exec(int signum)
{
	g_glb = 130;
    (void)signum;
    printf("\n");
}

void	handle_signals_exec()
{
	g_glb = 0;
	signal(SIGINT, &sighandler_exec);
}
