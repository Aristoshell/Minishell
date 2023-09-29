/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:22:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/26 17:23:52 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_simple_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

bool	ft_is_double_quote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

char	ft_is_quote(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (0);
}
