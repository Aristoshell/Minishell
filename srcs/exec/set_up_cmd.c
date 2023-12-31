/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:14:01 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/16 15:54:12 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

char	**list_to_array(t_envlist *list)
{
	int		i;
	int		j;
	char	**ret;

	i = ft_envlstsize(list);
	ret = ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if (list->flag == MASK_ENV)
		{
			ret[j] = join_lign_env(list);
			if (ret[j] == NULL)
				return (NULL);
			j++;
		}
		list = list->next;
	}
	ret[j] = NULL;
	return (ret);
}

int	handle_builtins2(t_cmd **cmd, t_data *data, t_pipe *pipes)
{
	if (cmd[data->current_cmd]->cmd_type == cmd_unset)
		return (unset(&data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_env)
		return (display_env(data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_exit)
		return (bt_exit(data, data->current_cmd, pipes));
	return (0);
}

int	handle_builtins(t_data *data, t_pipe *pipes)
{
	t_cmd	**cmd;

	cmd = data->cmd;
	if (cmd[data->current_cmd]->cmd_type == no_cmd)
	{
		if (data->exec_val == 130)
			return (130);
		return (1);
	}
	else if (cmd[data->current_cmd]->cmd_type == cmd_echo)
		return (bt_echo(data, data->current_cmd));
	else if (cmd[data->current_cmd]->cmd_type == cmd_cd)
		return (bt_cd(data));
	else if (cmd[data->current_cmd]->cmd_type == cmd_pwd)
		return (bt_pwd(data));
	else if (cmd[data->current_cmd]->cmd_type == cmd_export)
		return (export(&data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_export_print)
		return (display_export(data->envp, cmd[data->current_cmd]->cmd_args));
	return (handle_builtins2(cmd, data, pipes));
}
