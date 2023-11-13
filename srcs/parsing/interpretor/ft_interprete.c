/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interprete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:17 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:56:18 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_count_cmd(t_list *list, t_data *data)
{
	t_token	*curr_tok;

	data->nb_command = 1;
	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_pipe)
			data->nb_command += 1;
		list = list->next;
	}
}

int	ft_init_tab_cmd(t_data *data)
{
	data->cmd = malloc(sizeof(t_cmd) * data->nb_command);
	if (!data->cmd)
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}

int	ft_fill_tab_cmd(t_data *data, t_list *list)
{
	t_token	*curr_token;

	data->current_cmd = 0;
	curr_token = (t_token *)list->content;
	while (data->current_cmd < data->nb_command)
	{
		if (ft_init_cmd(data, data->current_cmd)
			|| ft_fill_cmd(data->cmd[data->current_cmd], list, data))
			return (MEMORY_ERR_NB);
		ft_check_builtin(data->cmd[data->current_cmd]);
		data->current_cmd++;
		while (curr_token->type != type_pipe)
		{
			list = list->next;
			if (!list)
				return (FUNCTION_SUCCESS);
			curr_token = (t_token *)list->content;
		}
		list = list->next;
		curr_token = (t_token *)list->content;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_interprete(t_data *data)
{
	data->nb_command = 0;
	ft_count_cmd(data->tokens, data);
	if (ft_init_tab_cmd(data))
		return (MEMORY_ERR_NB);
	if (ft_fill_tab_cmd(data, data->tokens))
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}

	// printf("INTERPRETE\n");
	// ft_display_lexer(*data);