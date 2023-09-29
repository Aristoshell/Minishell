/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 15:02:13 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

t_token_type	get_token_type(const char *token)
{
	int	i;

	i = 0;
	if (token[i] == '|' && token[i + 1] == 0)
		return (type_pipe);
	else if (token[i] == '>' && token[i + 1] == 0)
		return (type_out);
	else if (token[i] == '>' && token[i + 1] == '>' && token[i + 2] == 0)
		return (type_append);
	else if (token[i] == '<' && token[i + 1] == 0)
		return (type_in);
	else if (token[i] == '<' && token[i + 1] == '<' && token[i + 2] == 0)
		return (type_heredoc);
	else
		return (type_word);
}
