/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_empty_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:58:18 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:58:20 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

bool	ft_check_empty_line(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] > 32)
			return (true);
		i++;
	}
	return (false);
}
