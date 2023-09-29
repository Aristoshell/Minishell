/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:01:09 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/17 15:02:39 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischarset(char const *charset, char to_check)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == to_check)
			return (1);
		i++;
	}
	return (0);
}

static int	count_charset(char const *s1, char const *charset)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s1))
	{
		if (ischarset((char *)charset, (char)s1[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

static int	rev_count_charset(char const *s1, char const *charset)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (ischarset((char *)charset, (char)s1[i]) == 0)
			return (i + 1);
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*final;
	int		i;

	i = 0;
	start = count_charset(s1, set);
	end = rev_count_charset(s1, set);
	final = malloc(sizeof(char) * end - start + 1);
	if (!final)
		return (NULL);
	while (start < end)
	{
		final[i] = (char)s1[start];
		i++;
		start++;
	}
	final[i] = '\0';
	return (final);
}
