/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 19:46:39 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_syntax(char	*str)
{
	if (check_open_quote(str) || check_redir(str) || check_pipe(str))
		return (/*printf("check_open_quote : %d || check_redir : %d || check_pipe : %d\n", check_open_quote(str), check_redir(str), check_pipe(str)),*/false);
	return (true);
}
