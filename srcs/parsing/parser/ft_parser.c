/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:59:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/29 16:39:35 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

// penser a initialiser les currents

// void	check_redirect_in(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	if (word[0])
// }

// void	fill_cmd(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	while (tokens[*curr_word]->type > type_pipe)
// 	{
// 		check_redirect_in(cmd, tokens, curr_cmd, curr_word);
// 	}	
// }

int	ft_fill_tab_cmd(t_data *data, t_info *info)
{
	int	i;

	i = 0;
	while (i < data->nb_command)
	{
		ft_init_cmd(data, i);
		if (i == 0)
		{
			if (ft_fill_cmd(data->cmd[i], data->cmd[i]->fd_out, info, true) != FUNCTION_SUCCESS)//vraiment a changer car degueu
				return (MEMORY_ERROR_NB);
		}
		else
		{
			if (ft_fill_cmd(data->cmd[i], data->cmd[i-1]->fd_out, info, false)!= FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB);
		}
		i++;
	}
	return (FUNCTION_SUCCESS);
}


int	ft_parser(t_info	*info, t_data *data)
{
	ft_count_cmd(*info, data);
	//checker si 0 cmd, normalement ce sera deja fait car 1) ligne vide renvoi juste le parseur, mais 2) attention avec envoi de just ""
	if (ft_init_tab_cmd(data) !=  FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	ft_fill_tab_cmd(data, info);
	//ft_display_tab_cmd(*data);
	//ft_reinit_data(data);
	return (0);
}
