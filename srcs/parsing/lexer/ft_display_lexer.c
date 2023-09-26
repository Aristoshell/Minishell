/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/26 19:26:28 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_lexer(t_info info)
{
	int i = 0;
	while(i < info.nb_tokens)
	{

		dprintf(STDERR_FILENO, "[%d] [%d]: %s\n", i, info.tokens[i]->type, info.tokens[i]->string);
		if (word_has_expand((const char*)info.tokens[i]->string))
			dprintf(STDERR_FILENO, GREEN"has expand\n"NC);
		else
			dprintf(STDERR_FILENO, RED"has no expand\n"NC);
		i++;
	}
}
