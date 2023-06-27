/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:44:58 by marine            #+#    #+#             */
/*   Updated: 2022/12/17 23:40:21 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*s2;

	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j]))
		j--;
	if ((j - i + 2) < 0)
		return (ft_strdup(""));
	s2 = malloc((j - i + 2) * sizeof(char));
	if (s2 == NULL)
		return (0);
	while (i < j +1)
	{
		s2[k] = s1[i];
		i++;
		k++;
	}
	s2[k] = 0;
	return (s2);
}
