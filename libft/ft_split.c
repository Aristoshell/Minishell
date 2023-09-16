/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:41:30 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/22 17:30:00 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**final_free(char **final, int i)
{
	while (i >= 0)
	{
		free(final[i]);
		i--;
	}
	free(final);
	return (NULL);
}

static int	pass_charset(const char *s, char c)
{
	int	to_pass;

	to_pass = 0;
	while (s[to_pass] == c && s[to_pass])
	{
		to_pass++;
	}
	return (to_pass);
}

static int	countwords(const char *s, char c)
{
	int	i;
	int	nbr_words;

	if (s[0] == '\0')
		return (0);
	i = pass_charset(s, c);
	nbr_words = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			nbr_words++;
			i += pass_charset((char *) &s[i], c) - 1;
		}
		i++;
	}
	if (s[i - 1] != c)
		nbr_words++;
	if (nbr_words == 0)
		nbr_words = 1;
	return (nbr_words);
}

static int	word_len(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	int		len;
	int		i;
	int		j;
	size_t	k;

	i = -1;
	k = pass_charset((char *) s, c);
	final = ft_calloc(sizeof(char **), countwords(s, c) + 1);
	if (!final)
		return (NULL);
	while (i++ < countwords(s, c) && k < ft_strlen(s))
	{
		j = -1;
		len = word_len((char *) &s[k], c);
		final[i] = malloc(sizeof(char) * len + 1);
		if (!final)
			return (final_free(final, i));
		while (j++ < len)
			final[i][j] = s[k++];
		final[i][j - 1] = '\0';
		if (k < ft_strlen(s))
			k += pass_charset((char *) &s[k], c);
	}
	return (final);
}
