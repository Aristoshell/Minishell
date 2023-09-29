/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:18:42 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

long unsigned	ft_strlen(const char *str)
{
	long unsigned	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	ft_clean_string(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	str = NULL;
}
