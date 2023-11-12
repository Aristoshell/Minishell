/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:12:41 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/12 17:04:08 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	check_n(char *arg)
{
	int	j;

	if (arg[0] != '-')
		return (0);
	j = 1;
	while (arg[j])
	{
		if (arg[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}

int	bt_echo(t_data *data, int to_do)
{
	int		i;
	int		n_option;
	int		printed;
	t_cmd	*cmd;

	cmd = data->cmd[to_do];
	n_option = 0;
	printed = 0;
	i = 0;
	while (cmd->cmd_args[++i])
	{
		if (printed == 1 || check_n(cmd->cmd_args[i]) == 0)
		{
			if (printed == 1)
				write(cmd->fd_out, " ", 1);
			if (ft_putstr_fd_checked(cmd->cmd_args[i], cmd->fd_out) == 1)
				return (1);
			printed = 1;
		}
		else
			n_option = 1;
	}
	if (n_option == 0)
		write(cmd->fd_out, "\n", 1);
	return (0);
}
