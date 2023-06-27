/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:55:34 by madavid           #+#    #+#             */
/*   Updated: 2022/12/15 17:30:32 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
