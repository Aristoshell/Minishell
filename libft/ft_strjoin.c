/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 08:43:27 by lmarchai            #+#    #+#           */
/*   Updated: 2022/10/15 08:43:27 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int				len_tot;
	unsigned int	i;
	char			*res;

	len_tot = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof (char) * len_tot + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	res[len_tot] = '\0';
	return (res);
}
