/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:22:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/14 11:54:02 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_space(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}

char	is_quote(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (0);
}

bool	is_op(char c)
{
	if (c == '>' || c == '<' || c == '|') // || (c == '>' && next == '>')|| (c == '<' && next == '<'))
		return (true);
	return (false);
}

bool	is_separator(char c)
{
	if (is_op(c) || is_space(c))
		return (true);
	return (false);
}
bool	is_cmd_separator(char c)
{
	if (c == '|' || c == ';' || c == '&')
		return (true);
	return (false);
}