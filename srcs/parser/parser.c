/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:14:02 by marine            #+#    #+#             */
/*   Updated: 2023/07/06 10:42:14 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *word)
{
	if (word[0] == '-' && ft_isprint(word[1]) == 1)
		return (1);
	return (0);
}

int	is_builtin(char *word)
{
	
}

void	parser(t_lexer *node)
{
	
	while (node)
	{
		while (node.)
	}
	
}
