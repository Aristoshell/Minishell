/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:39:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/15 00:10:19 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	clean_exit(t_data *data, t_pipe *pipes)
{
	if (data->nb_command > 1)
		close_pipes(data, pipes);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	ft_clean_t_data(data);
	free(pipes);
}

void	error_exit(t_cmd *cmd, t_data *data, t_pipe *pipes)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	ft_dprintf(STDERR_FILENO, "minishell: exit: %s: \
		numeric argument required\n", cmd->cmd_args[1]);
	clean_exit(data, pipes);
	exit(2);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_too_many_args(void)
{
	ft_dprintf(2, "exit: too many arguments\n");
	return (1);
}

int	bt_exit(t_data *data, int i, t_pipe *pipes)
{
	int		exit_val;
	t_cmd	*built_cmd;

	built_cmd = data->cmd[i];
	exit_val = 0;
	if (!built_cmd->cmd_args[1])
	{
		if (data->nb_command == 1)
			ft_dprintf(STDERR_FILENO, "exit\n");
		clean_exit(data, pipes);
		exit(0);
	}
	if (ft_isnumber((built_cmd->cmd_args[1])))
	{
		if (built_cmd->cmd_args[2] != NULL)
			return (exit_too_many_args());
		exit_val = ft_atoi(built_cmd->cmd_args[1]) % 256;
	}
	else
		error_exit(built_cmd, data, pipes);
	if (data->nb_command == 1)
		ft_dprintf(STDERR_FILENO, "exit\n");
	clean_exit(data, pipes);
	exit(exit_val);
	return (0);
}
