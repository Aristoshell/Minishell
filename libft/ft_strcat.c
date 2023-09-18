/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:00:31 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 09:22:17 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcat(char *src, char *dest)
{
	char *new;
	int total;
	int	i;
	int j;

	if (!src || !dest)
		return (NULL);
	total = ft_strlen(src) + ft_strlen(dest);
	new = malloc(sizeof(char) * total + 1);
	if (!new)
		return (NULL);
	i = 0;
	while(src[i])
	{
		new[i] = src[i];
		i++;  
	}
	j = 0;
	while(dest[j])
	{
		new[i + j] = dest[j];
		j++;
	}
	new[i+j] = '\0';
	free(src);
	return(new);
}