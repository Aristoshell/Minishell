/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:55:55 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:55:56 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_check_builtin(t_cmd *cmd)
{
	if (!cmd->cmd_args || !cmd->cmd_args[0])
		return (cmd->cmd_type = no_cmd, 0);
	if (!ft_strncmp("echo", cmd->cmd_args[0], (ft_strlen("echo") + 1)))
		cmd->cmd_type = cmd_echo;
	else if (!ft_strncmp("cd", cmd->cmd_args[0], (ft_strlen("cd") + 1)))
		cmd->cmd_type = cmd_cd;
	else if (!ft_strncmp("pwd", cmd->cmd_args[0], (ft_strlen("pwd") + 1)))
		cmd->cmd_type = cmd_pwd;
	else if (!ft_strncmp("env", cmd->cmd_args[0], (ft_strlen("env") + 1)))
		cmd->cmd_type = cmd_env;
	else if (!ft_strncmp("export", cmd->cmd_args[0], (ft_strlen("export") + 1)))
	{
		if (cmd->cmd_args[1] && cmd->cmd_args[1][0] != '-')
			cmd->cmd_type = cmd_export;
		else
			cmd->cmd_type = cmd_export_print;
	}
	else if (!ft_strncmp("unset", cmd->cmd_args[0], (ft_strlen("unset") + 1)))
		cmd->cmd_type = cmd_unset;
	else if (!ft_strncmp("exit", cmd->cmd_args[0], (ft_strlen("exit") + 1)))
		cmd->cmd_type = cmd_exit;
	else
		cmd->cmd_type = no;
	return (0);
}
