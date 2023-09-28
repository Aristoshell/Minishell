/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_fill_tab_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:35:05 by madavid           #+#    #+#             */
/*   Updated: 2023/09/28 16:57:30 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_info *info, int nb_args)
{
	int i = 0;
	while (i < nb_args)
	{
		{//creer les autres
			cmd->cmd_args[i] = ft_strdup((const char*)info->tokens);
			if (!cmd->cmd_args[i])
				return (MEMORY_ERROR_NB); // GRRRRR
		}
		i++;
		info->current_token++;
	}
	i++;
	if (i == nb_args)
	{//create last qui va etre egal a NULL
		cmd->cmd_args[i] = malloc(sizeof(char) * 1);	
		if (!cmd->cmd_args[i])
			return (MEMORY_ERROR_NB); // GRRRRR
		cmd->cmd_args[i][0] = '\0';
	}
	return (FUNCTION_SUCCESS);
}
