/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 15:02:13 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_get_token_val_len_manage_quote(char c, bool	*in_quote, char *quote_type)
{
	if (ft_is_quote(c) && c == *quote_type)
	{
		*in_quote = false;
		*quote_type = 0;
	}
	else if (!(*in_quote) && ft_is_quote(c))
	{
		*in_quote = true;
		*quote_type = c;
	}
}

int		ft_get_token_val_len(const char *p, int *i)
{
	bool		in_quote;
	char		quote_type;
	int			len;

	in_quote = false;
	len = 0;
	quote_type = 0;
	if (!p[*i])
		return (*i += 1, 0);
	while (p[*i] && ft_is_space(p[*i]))
		*i += 1;
	if (ft_is_operator(p[*i]))
	{
		if ((p[*i] == '>' && p[*i+1] == '>') || (p[*i] == '<' && p[*i+1] == '<'))
			return (*i += 2, 2);
		return (*i += 1, 1);
	}
	while (p[*i] && (in_quote || (!in_quote && !ft_is_separator(p[*i]))))
	{
		ft_get_token_val_len_manage_quote(p[*i], &in_quote, &quote_type);
		*i += 1;
		len++;
	}
	return (len);
}

void	ft_fill_token_val(char	*buffer, const char *str, int size, int i)
{
	int	position;
	int	j;

	position = i - size;
	j = 0;
	while (j < size)
	{
		buffer[j] = str[position];
		j++;
		position++;
	}
	buffer[j] = 0;
}

char	*get_token_val(const char *input, int *i)
{
	char	*word;
	int		size;

	size = ft_get_token_val_len(input, i);
	if (size == 0)
		return (NULL);
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (MEMORY_ERROR_PT); // penser a free ce qui a ete malloc avant aussi
	ft_fill_token_val(word, input, size, *i);
	return (word);
}
