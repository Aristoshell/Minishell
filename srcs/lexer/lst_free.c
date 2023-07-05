/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:57:48 by marine            #+#    #+#             */
/*   Updated: 2023/07/05 15:20:25 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer_del_one(t_lexer *node)
{
	free (node->word);
	node->word = NULL;
	free (node);
}

void	ft_lexer_clear(t_lexer **node)
{
	t_lexer	*p;

	if (node)
	{
		p = *node;
		while (*node)
		{
			p = (*node)->next;
			ft_lexer_del_one(*node);
			*node = p;
			//surement des leaks lol
		}
	}
}
