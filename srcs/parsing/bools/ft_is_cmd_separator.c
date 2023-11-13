/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_cmd_separator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:58:22 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:58:23 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_cmd_separator(char c)
{
	if (c == '|')
		return (true);
	return (false);
}
