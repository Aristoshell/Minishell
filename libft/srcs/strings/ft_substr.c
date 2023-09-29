/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:20:16 by marine            #+#    #+#             */
/*   Updated: 2023/09/18 00:10:11 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s_;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		len = 0;
	if (len > i - start)
		len = i - start;
	s_ = malloc((len + 1) * sizeof(char));
	if (s_ == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s_[i] = s[start + i];
		i++;
	}
	s_[i] = '\0';
	return (s_);
}
