/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:50:52 by marine            #+#    #+#             */
/*   Updated: 2022/12/18 10:56:06 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*s_new;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s_new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s_new == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s_new[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		s_new[i] = s2[j];
		i++;
		j++;
	}
	return (s_new[i] = 0, s_new);
}
