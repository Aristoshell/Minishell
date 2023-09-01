/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:57:48 by marine            #+#    #+#             */
/*   Updated: 2023/08/08 16:10:35 by madavid          ###   ########.fr       */
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
			printf("node : %s\n", (*node)->word);
			p = (*node)->next;
			ft_lexer_del_one(*node);
			*node = p;
			//surement des leaks lol
		}
	}
}
