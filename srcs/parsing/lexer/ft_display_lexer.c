/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 18:10:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_lexer(t_info info)
{
	int i = 0;
	while(i < info.nb_tokens)
	{
		dprintf(STDERR_FILENO, "[%d] [%d]: %s\n", i, info.tokens[i]->type, info.tokens[i]->string);
		i++;
	}
}