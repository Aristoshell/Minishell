/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_pass_when_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:57:40 by madavid           #+#    #+#             */
/*   Updated: 2023/09/22 12:57:49 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_pass_when_quote(const char *str, int *i)
{
	char	quote;

	while (str[*i])
	{
		quote = str[*i];
			*i += 1;
		while (str[*i] != quote)
			*i += 1;
		*i += 1;
		if (!ft_is_quote(str[*i]))
			return ;
	}
}