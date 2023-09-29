/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:40:32 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/09 21:26:36 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *pointer, int searchedChar, size_t size)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)pointer;
	i = 0;
	while (i < size)
	{
		if (str[i] == (unsigned char)searchedChar)
			return (str + i);
		i++;
	}
	return (NULL);
}
