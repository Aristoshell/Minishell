/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/15 19:12:21 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	check_start(char *str, int *i)
{
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	if (str[*i] == '>')
		return (false);
	return (true);
}

bool	check_redir_to(char *str, int *i)
{
	*i += 1;
	if (str[*i] == '>')
		*i += 1;
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir_from(char *str, int *i)
{
	*i += 1;
	if (str[*i] == '<')
		*i += 1;
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!i && !check_start(str, &i))
			return (printf("check start\n"), true);
		if (str[i] == '<')
		{	
			if (!check_redir_from(str, &i))
				return (printf("check redir from\n"), true);
		}
		else if (str[i] == '>')
		{	
			if (!check_redir_to(str, &i))
				return (printf("check redir to\n"), true);
		}
		else
			i++;
	}
	return (false);
}

bool	check_syntax(char	*str)
{
	if (check_open_quote(str) || check_redir(str) || check_pipe(str))
		return (/*printf("check_open_quote : %d || check_redir : %d || check_pipe : %d\n", check_open_quote(str), check_redir(str), check_pipe(str)),*/false);
	return (true);
}
