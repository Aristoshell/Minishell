/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:37:30 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:37:31 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
