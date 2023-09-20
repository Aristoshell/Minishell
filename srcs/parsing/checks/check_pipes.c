/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 19:49:26 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_data_check_pipe(char c, bool	*check, bool *wrd)
{
	if (ft_is_pipe(c))
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
		if (!ft_is_quote(str[*i]))
			return ;
	}
}

bool	check(char c, bool pipe, bool word)
{
	bool	two_pipes;
	bool	first_ft_is_pipe;
	bool	last_ft_is_pipe;

	two_pipes = (ft_is_pipe(c) && pipe);
	first_ft_is_pipe = (ft_is_pipe(c) && !word);
	last_ft_is_pipe = (!c && pipe);
	if (two_pipes || first_ft_is_pipe || last_ft_is_pipe)
		return (false);
	return (true);
}

bool	check_pipe(char *str)
{
	int		i;
	bool	pipe;
	bool	wrd;

	i = -1;
	pipe = false;
	wrd = false;
	while (str[++i])
	{
		while (str[i] && ft_is_space(str[i]) == 1)
			i++;
		if (!check(str[i], pipe, wrd))
			return (true);
		if (ft_is_quote(str[i]))
			pass_when_quote(str, &i);
		if (str[i])
			change_data_check_pipe(str[i], &pipe, &wrd);
	}
	if (!str[i] && pipe)
		return (true);
	return (false);
}
