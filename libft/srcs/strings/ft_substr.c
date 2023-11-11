/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:38:19 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:38:20 by lmarchai         ###   ########.fr       */
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
