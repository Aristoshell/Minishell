/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:55:14 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:55:16 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	parsing(t_data *data, const char *input)
{
	if (ft_check_open_quote_bool(input) || !ft_check_empty_line(input, 0))
		return (FUNCTION_SUCCESS);
	if (ft_tokenise(input, data))
		return (MEMORY_ERR_NB);
	if (ft_check_syntax_with_tokens(data->tokens))
	{
		if (ft_del_quotes(data) || ft_expand(data->envp, data)
			|| ft_join_nodes(data->tokens, data) || ft_interprete(data))
		{
			ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
			data->tokens = NULL;
			return (MEMORY_ERR_NB);
		}
	}
	else
		data->exec_val = 2;
	ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
	data->tokens = NULL;
	return (FUNCTION_SUCCESS);
}
