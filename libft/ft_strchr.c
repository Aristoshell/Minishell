/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:37:44 by lmarchai            #+#    #+#           */
/*   Updated: 2022/10/14 11:37:44 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int to_find)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((char)to_find == s[i])
			return (s + i);
		i++;
	}
	if (to_find == '\0')
		return (s + i);
	return (NULL);
}
