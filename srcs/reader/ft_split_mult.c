/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/08/30 17:43:01 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "../libft/libft.h"

static int	countword(char const *s, char *charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (ft_strchr(charset, s[i]) && s[i] != 0)
			i++;
		if (!ft_strchr(charset, s[i]) && s[i] != 0)
			counter++;
		while (!ft_strchr(charset, s[i]) && s[i] != 0)
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

char	**ft_split_mult(char const *s, char *charset)
{
	// char	**s_splitted;
	// int		words;
	// int		chars;
	// int		i;

	// words = 0;
	// i = 0;
	if (!s)
		return (NULL);
	int wordcount = countword(s, charset);
	// s_splitted = malloc((countword(s, charset) + 1) * sizeof(char *));
	// if (s_splitted == NULL)
	// 	return (NULL);
	// while (words < countword(s, c))
	// {
	// 	chars = 0;
	// 	while (s[i] && s[i] == c)
	// 		i++;
	// 	s_splitted[words] = malloc((countlenword(&s[i], c) + 1) * sizeof(char));
	// 	if (!s_splitted[words])
	// 		return (NULL);
	// 	while (s[i] && s[i] != c)
	// 		s_splitted[words][chars++] = s[i++];
	// 	s_splitted[words++][chars] = 0;
	// }
	// return (s_splitted[words] = NULL, s_splitted);
	return(NULL);
}

int	main(void)
{
	ft_split_mult("Wesh|alors > hihi < grr")
}