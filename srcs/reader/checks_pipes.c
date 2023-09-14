/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/14 12:56:17 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

void	change_data_check_pipe(char c, bool	*check, bool *wrd)
{
	if (is_pipe(c))
		*check = true;
	else
		*check = false;
	if (!*wrd)
		*wrd = true;
}

void	pass_when_quote(char *str, int *i)
{
	char	quote;

	while (str[*i])
	{
		quote = str[*i];
			*i += 1;
		while (str[*i] != quote)
			*i += 1;
		*i += 1;
		if (!is_quote(str[*i]))
			return ;
	}
}

bool	check(char c, bool pipe, bool word)
{
	bool	two_pipes;
	bool	first_is_pipe;
	bool	last_is_pipe;

	two_pipes = (is_pipe(c) && pipe);
	first_is_pipe = (is_pipe(c) && !word);
	last_is_pipe = (!c && pipe);
	if (two_pipes || first_is_pipe || last_is_pipe)
		return (false);
	return (true);
}

int	check_pipe(char *str)
{
	int		i;
	bool	pipe;
	bool	wrd;

	i = -1;
	pipe = false;
	wrd = false;
	while (str[++i])
	{
		while (str[i] && is_space(str[i]) == 1)
			i++;
		if (!check(str[i], pipe, wrd))
			return (false);
		if (is_quote(str[i]))
			pass_when_quote(str, &i);
		if (str[i])
			change_data_check_pipe(str[i], &pipe, &wrd);
	}
	if (!str[i] && pipe)
		return (false);
	return (true);
}
