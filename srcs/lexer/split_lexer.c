/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:47:29 by marine            #+#    #+#             */
/*   Updated: 2023/08/01 17:45:05 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_printable(char c)
{
	if (c >= 33 && c <= 127)
		return (1);
	return (0);
}

static int	countword(char const *s)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (is_printable(s[i]) == 0 && s[i] != 0)
			i++;
		if (is_printable(s[i]) == 1 && s[i] != 0)
			counter++;
		while (is_printable(s[i]) == 1 && s[i] != 0)
			i++;
	}
	return (counter);
}

static int	countlenword(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (is_printable(s[i]) == 0 && s[i] != 0)
		i++;
	while (is_printable(s[i]) == 1 && s[i] != 0)
	{
		i++;
		count++;
	}
	return (count);
}

void	clear_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
		free(split[i++]);
	free(split);
}

char	*ft_split_lexer(char const *str, int *i)
{
	char			*word;
	int				len_word;
	t_open_quote	open_quote;
	int				j;
	int				last_is_backslash;

	len_word = 0;
	open_quote = no;
	j = 0;
	if (!str)
		return (NULL);
	while (str[*i])
	{
		if (is_meta(str[*i]) == 1)
		{
			word = malloc (sizeof(char) * 2);
			if (word == NULL)
				return (NULL);
			word[0] = str[*i];
			word[1] = 0;
		}
		while (str[*i] && is_printable(str[*i]) == 0) /sauter les espaces debut
		{
			*i++;
			j++;
		}
		while(str[*i] && is_printable(str[*i]) == 1 &&)
		{
			
		}


		word = malloc((len_word + 1) * sizeof(char));
		if (word)
			return (NULL);
		while (str[i] && is_printable(str[i]) == 1)
			tab[words][chars++] = str[i++];
		tab[words++][chars] = 0;
	}
	return (word);
}
