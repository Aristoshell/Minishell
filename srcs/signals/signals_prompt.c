/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/10 23:59:23 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	handle_signals_prompt(t_data *data)
{
	printf("prompt\n");
	if (g_glb == 130)
		data->exec_val = 130;
	g_glb = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
}
