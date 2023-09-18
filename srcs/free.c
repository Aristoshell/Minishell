/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:52:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 11:21:55 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_list_args(t_cmd *cmd[4], t_pipe *pipes, int len_list)
{
	int	i;
	int	j;

	i = 0;
	while (i < len_list)
	{
		j = 0;
		while (cmd[i]->cmd_args[j])
		{
			free(cmd[i]->cmd_args[j]);
			j++;
		}
		free(cmd[i]->cmd_args);
		free(cmd[i]);
		i++;
	}
	free(pipes);
}
