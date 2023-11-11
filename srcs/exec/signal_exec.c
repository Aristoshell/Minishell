/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:41:03 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 16:47:05 by lmarchai         ###   ########.fr       */
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
	(void)signum;
	signal(SIGINT, &sighandler_exec2);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signals_exec(void)
{
	signal(SIGCHLD, &sighandler_exec);
}
