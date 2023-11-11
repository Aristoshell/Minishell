/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:57:54 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 14:11:38 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	check_params(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-')
			return (0);
		else if (ft_is_space(str[i]))
			i++;
		else
			return (1);
	}
	return (1);
}

void	print_dashes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < 2)
	{
		ft_dprintf(2, "%c", str[i]);
		i++;
	}
}

int	print_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	return (1);
}

int	bt_pwd(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	cmd = data->cmd[data->current_cmd];
	if (!cmd->cmd_args[1])
		return (print_pwd());
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (check_params(data->cmd[data->current_cmd]->cmd_args[i]) == 0)
			return (print_pwd());
		i++;
	}
	ft_dprintf(2, "pwd: ");
	print_dashes(data->cmd[data->current_cmd]->cmd_args[1]);
	ft_dprintf(2, ": invalid option\n");
	return (2);
}
