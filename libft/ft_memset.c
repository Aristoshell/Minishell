/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:02:15 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/16 22:16:42 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	int				i;
	unsigned char	*char_pointer;

	char_pointer = pointer;
	i = 0;
	while (count > 0)
	{
		char_pointer[i] = value;
		i++;
		count--;
	}
	return (char_pointer);
}
