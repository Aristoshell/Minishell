/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:13:14 by lmarchai            #+#    #+#           */
/*   Updated: 2022/08/23 20:13:14 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*newsrc;
	int		len_src;
	int		i;

	len_src = ft_strlen(src);
	newsrc = malloc(len_src * sizeof(char) + 1);
	if (!newsrc)
		return (NULL);
	i = 0;
	while (i < len_src)
	{
		newsrc[i] = src[i];
		i++;
	}
	newsrc[i] = '\0';
	return (newsrc);
}
