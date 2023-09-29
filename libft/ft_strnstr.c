/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:20:54 by lmarchai            #+#    #+#           */
/*   Updated: 2022/10/14 13:20:54 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	if (ft_strlen(str) == 0 || ft_strlen(str) < ft_strlen(to_find) || len == 0)
		return (0);
	while (str[i] && len - i >= ft_strlen(to_find))
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j])
			{
				j++;
				if (j == ft_strlen(to_find))
					return ((char *) str + i);
			}
		}
		i++;
	}
	return (0);
}
