/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_tab_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:09:43 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_tab_cmd(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data.nb_command)
	{
		printf(BLUE"cmd %d\n"NC, i);
		j = 0;
		while (data.cmd[i] && data.cmd[i]->cmd_args[j] && data.cmd[i]->cmd_args[j][0])
		{
			printf("cmd[%d] arg[%d] : %s\n", i, j, data.cmd[i]->cmd_args[j]);
			j++;
		}
		printf("in : %d, out : %d\n", data.cmd[i]->input, data.cmd[i]->output);
		printf("\n");
		i++;
	}
}
