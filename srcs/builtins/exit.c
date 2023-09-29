/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:48:33 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"



int	ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	bt_exit(t_cmd **cmd, int i)
{
	int	exit_val;
	t_cmd *built_cmd;

	built_cmd = cmd[i];
	exit_val = 0;
	if (!built_cmd->cmd_args[1])
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_isnumber((built_cmd->cmd_args[1])))
	{
		if (built_cmd->cmd_args[2] != NULL)
		{
			//set la value de retour a 1
			printf("exit: too many arguments\n");
			return ;
		}
		exit_val = ft_atoi(built_cmd->cmd_args[1]) % 256;
	}
	else
		error_management(built_cmd, "exit: numeric argument required", 2);
	//free tout ce que l'on peut
	printf("exit\n");
	exit(exit_val);
}