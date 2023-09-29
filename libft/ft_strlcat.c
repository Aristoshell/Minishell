/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:29:27 by lmarchai            #+#    #+#           */
/*   Updated: 2022/08/23 20:29:27 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;

	if (size == 0 || size <= ft_strlen(dest))
		return (ft_strlen(src) + size);
	i = 0;
	len_dst = ft_strlen(dest);
	while (src[i] && (i + len_dst) < (size - 1))
	{
		dest[i + len_dst] = src[i];
		i++;
	}
	dest[i + len_dst] = '\0';
	return (len_dst + ft_strlen(src));
}
