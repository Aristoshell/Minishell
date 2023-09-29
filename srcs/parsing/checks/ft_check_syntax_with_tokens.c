/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_with_tokens.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:24 by madavid           #+#    #+#             */
/*   Updated: 2023/09/26 15:31:11 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_check_syntax_with_tokens(t_info info)
{
	int				i;
	t_token_type	curr;
	t_token_type	prev;
	
	i = 0;
	while (i < info.nb_tokens)
	{
		curr = info.tokens[i]->type;
		if (i == 0)
		{	
			if (curr == type_pipe)
				return (false);
		}
		else
		{
			if (prev == type_pipe && curr == type_pipe)
				return (false);
			else if ((prev == type_in || prev == type_out || prev == type_append || prev == type_heredoc) && curr == type_pipe)
				return (false);
			else
				;
		}
		prev = curr;
		i++;
	}
	if (prev != type_word)
		return (false);
	return (true);
}
