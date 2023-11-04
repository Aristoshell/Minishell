/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/04 13:40:31 by lmarchai         ###   ########.fr       */
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

void handle_signals_heredoc(t_data *data)
{
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
	if (g_glb == 130)
		data->exec_val = 130;
	g_glb = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_DFL);
}


static void    sighandler_exec(int signum)
{
	g_glb = 130;
    (void)signum;
    printf("\n");
}

void	handle_signals_exec(t_data *data)
{
	if (g_glb == 130)
	{
		data->exec_val = 130;
		printf("%d\n", data->exec_val);
	}
	g_glb = 0;
	signal(SIGINT, &sighandler_exec);
	signal(SIGQUIT, SIG_DFL);
}
