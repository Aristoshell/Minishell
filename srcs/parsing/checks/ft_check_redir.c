/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

bool	check_start(const char *str, int *i)
{
	while (str[*i] && ft_is_space(str[*i]))
		*i += 1;
	if (ft_is_quote(str[*i]))
		ft_pass_when_quote(str, i);
	if (str[*i] == '>')
		return (false);
	return (true);
}

bool	check_redir_to(const char *str, int *i)
{
	*i += 1;
	if (str[*i] == '>')
		*i += 1;
	while (str[*i] && ft_is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (ft_is_quote(str[*i]))
		ft_pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir_from(const char *str, int *i)
{
	*i += 1;
	if (str[*i] == '<')
		*i += 1;
	while (str[*i] && ft_is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (ft_is_quote(str[*i]))
		ft_pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir(const char *str)
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
