/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_join_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:38 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 02:58:59 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_join_case_1(t_list *list, t_data *data)
{
	t_list	*save;

	save = list->next->next;
	ft_lstdelone(list->next, (void *)ft_clean_token);
	list->next = save;
	data->curr_token->join_with_next = false;
}

int	ft_join_case_2(t_list *list, t_data *data, t_token *next_tok)
{
	char	*join;
	t_list	*save;

	join = ft_strjoin_ms(data->curr_token->string, next_tok->string);
	if (!join)
		return (MEMORY_ERR_NB);
	free(data->curr_token->string);
	data->curr_token->string = join;
	data->curr_token->join_with_next = next_tok->join_with_next;
	save = list->next->next;
	ft_lstdelone(list->next, (void *)ft_clean_token);
	list->next = save;
	return (FUNCTION_SUCCESS);
}

int	ft_join_nodes(t_list *list, t_data *data)
{
	t_token	*next_tok;
	t_list	*next_node;

	while (list)
	{
		data->curr_token = (t_token *)list->content;
		if (!data->curr_token->join_with_next)
			list = list->next;
		else
		{
			next_node = list->next;
			if (next_node)
				next_tok = (t_token *)next_node->content;
			if (!data->curr_token->string && (!next_node || !next_tok->string))
				ft_join_case_1(list, data);
			else
				ft_join_case_2(list, data, next_tok);
		}
	}
	return (FUNCTION_SUCCESS);
}
