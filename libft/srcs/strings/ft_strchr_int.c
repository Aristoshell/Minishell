/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:37:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:37:28 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

int	ft_strchr_int(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == (unsigned char) c)
			return (i);
		i++;
	}
	return (-1);
}
