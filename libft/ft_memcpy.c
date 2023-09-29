/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:10:34 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/09 21:13:18 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	size_t			i;
	unsigned char	*to_cpy;
	unsigned char	*dest;

	dest = destination;
	if (destination == NULL && source == NULL)
		return (dest);
	to_cpy = (unsigned char *)source;
	i = 0;
	while (i < size)
	{
		dest[i] = to_cpy[i];
		i++;
	}
	return (dest);
}
