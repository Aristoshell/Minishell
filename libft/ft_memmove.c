/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:36:43 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/10 14:40:40 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*to_cpy;
	unsigned char	*dest;

	dest = destination;
	if (destination == NULL && source == NULL)
		return (dest);
	if (destination > source)
	{
		to_cpy = (unsigned char *)source;
		while (size > 0)
		{
			dest[size - 1] = to_cpy[size - 1];
			size--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(destination, source, size));
}
