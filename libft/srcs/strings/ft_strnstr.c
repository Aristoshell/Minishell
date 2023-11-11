/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:38:09 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:38:11 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*big_;

	i = 0;
	big_ = (char *)big;
	if (ft_strlen(little) > len)
		return (NULL);
	if (ft_strlen(little) == 0)
		return (big_);
	while (i <= len - ft_strlen(little) && big_[i])
	{
		if (ft_strncmp(&big_[i], little, ft_strlen(little)) == 0)
			return (&big_[i]);
		i++;
	}
	return (NULL);
}
