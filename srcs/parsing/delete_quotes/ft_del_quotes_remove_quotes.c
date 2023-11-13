/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quotes_remove_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:58 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:59 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_remove_quotes(t_list *list, char quote)
{
	t_token	*current_token;
	char	*curr_word;

	current_token = (t_token *)list->content;
	if (quote == DOUBLE_QUOTE)
		current_token->quote = double_q;
	else
		current_token->quote = simple_q;
	current_token->string[ft_strlen(current_token->string) - 1] = 0;
	curr_word = ft_strdup(&current_token->string[1]);
	if (!curr_word)
		return (MEMORY_ERR_NB);
	free(current_token->string);
	current_token->string = curr_word;
	return (FUNCTION_SUCCESS);
}
