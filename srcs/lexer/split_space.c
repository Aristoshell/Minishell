/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:47:29 by marine            #+#    #+#             */
/*   Updated: 2023/07/05 12:33:14 by marine           ###   ########.fr       */
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

char	**ft_split_space(char const *str)
{
	char	**tab;
	int		words;
	int		chars;
	int		i;

	words = 0;
	i = 0;
	if (!str)
		return (NULL);
	tab = malloc((countword(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (words < countword(str))
	{
		chars = 0;
		while (str[i] && is_printable(str[i]) == 0)
			i++;
		tab[words] = malloc((countlenword(&str[i]) + 1) * sizeof(char));
		if (!tab[words])
			return (clear_split(tab, words), NULL);
		while (str[i] && is_printable(str[i]) == 1)
			tab[words][chars++] = str[i++];
		tab[words++][chars] = 0;
	}
	return (tab[words] = NULL, tab);
}
