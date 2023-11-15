/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:37:23 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/15 22:29:56 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

static int	countword(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] != c && s[i] != 0)
			counter++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (counter);
}

static int	countlenword(char const *s, char charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] == charset && s[i] != 0)
		i++;
	while (s[i] != charset && s[i] != 0)
	{
		i++;
		count++;
	}
	return (count);
}

char	*clean(char **tab, int words)
{
	int	i;

	i = 0;
	while (i <= words)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**s_splitted;
	int		words;
	int		chars;
	int		i;

	words = 0;
	i = 0;
	if (!s)
		return (NULL);
	s_splitted = malloc((countword(s, c) + 1) * sizeof(char *));
	if (s_splitted == NULL)
		return (NULL);
	while (words < countword(s, c))
	{
		chars = 0;
		while (s[i] && s[i] == c)
			i++;
		s_splitted[words] = malloc((countlenword(&s[i], c) + 1) * sizeof(char));
		if (!s_splitted[words])
			return (NULL);
		while (s[i] && s[i] != c)
			s_splitted[words][chars++] = s[i++];
		s_splitted[words++][chars] = 0;
	}
	return (s_splitted[words] = NULL, s_splitted);
}
