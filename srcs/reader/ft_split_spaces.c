/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/06 14:48:35 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_space(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}

char	is_quote(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (0);
}

bool	is_op(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

bool	is_separator(char c)
{
	if (is_op(c) || is_space(c))
		return (true);
	return (false);
}

/* compte la taille de chaque mot */
void	get_part_len_manage_quote(char c, bool	*in_quote, char *quote_type)
{
	if (is_quote(c) && c == *quote_type)
	{
		*in_quote = false;
		*quote_type = 0;
	}
	else if (!(*in_quote) && is_quote(c))
	{
		*in_quote = true;
		*quote_type = c;
	}
}

int	get_part_len(char *p)
{
	int			i;
	bool		in_quote;
	char		quote_type;
	int			len;

	i = 0;
	in_quote = false;
	len = 0;
	quote_type = 0;
	while (p[i] && is_space(p[i]))
		i++;
	if (!p[i])
		return (0);
	if (is_op(p[i]))
		return (1);
	while (p[i] && (in_quote || (!in_quote && !is_separator(p[i]))))
	{
		get_part_len_manage_quote(p[i], &in_quote, &quote_type);
		i++;
		len++;
	}
	return (len);
}

/* fin compte la taille de chaque mot */

int	main(void)
{
	int	size;

	size = get_part_len(" \"'omg'grr | py\"\"une\" ");
	printf("size : %d\n", size);
}
