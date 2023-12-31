/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:38:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:38:17 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

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
