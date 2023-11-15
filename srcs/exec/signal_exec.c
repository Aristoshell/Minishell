/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:41:03 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/15 07:49:53 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_exec(int signum)
{
	g_glb = 130;
	(void)signum;
}

void	reset_signals(void)
{
	signal(SIGINT, &sighandler_exec);
	signal(SIGQUIT, SIG_DFL);
}

void	pouet(int signum)
{
	(void)signum;
}

void	handle_signals_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
