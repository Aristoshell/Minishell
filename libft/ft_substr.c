/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:29:55 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/15 20:58:55 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*final;
	int					total;
	unsigned int		i;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len < ft_strlen(s))
		total = len + 1;
	else
		total = ft_strlen(s) - start + 1;
	final = ft_calloc(total, sizeof(char));
	if (!final || !s)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		final[i] = s[start];
		i++;
		start++;
	}
	return (final);
}
