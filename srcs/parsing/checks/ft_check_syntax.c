/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

bool	check_syntax(const char	*str)
{
	if (check_open_quote(str)/* || check_redir(str) || check_pipe(str)*/)
		return (/*printf("check_open_quote : %d || check_redir : %d || check_pipe : %d\n", check_open_quote(str), check_redir(str), check_pipe(str)),*/false);
	return (true);
}


