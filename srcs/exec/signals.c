/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/09 17:22:46 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void    reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

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

void handle_signals_heredoc(t_data *data)
{
	printf(",heredoc\n");
	if (g_glb == 130)
		data->exec_val = 130;
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
	g_glb = 130;
	return ;
}

void    handle_signals_prompt(t_data *data)
{
	printf("prompt\n");
	if (g_glb == 130)
		data->exec_val = 130;
	g_glb = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler_exec2(int signum)
{
	(void)signum;
	printf("\n");
	g_glb = 130;
}

void	sighandler_exec(int signum)
{
	printf("exec\n");
	(void)signum;
	signal(SIGINT, &sighandler_exec2);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signals_exec()
{
	printf("child\n");
	signal(SIGCHLD, &sighandler_exec);
}
