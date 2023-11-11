/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/10 23:58:36 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

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

void	handle_signals_exec(void)
{
	printf("child\n");
	signal(SIGCHLD, &sighandler_exec);
}
