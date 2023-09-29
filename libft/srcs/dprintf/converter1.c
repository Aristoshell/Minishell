/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:44:50 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 13:51:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*get_char(int c, int *size)
{
	char	*str;

	*size += 1;
	str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = c;
	return (str);
}

char	*get_string(char *str, int *size)
{
	if (str == NULL)
	{
		*size += 6;
		return (ft_strdup("(null)"));
	}
	*size += ft_strlen(str);
	return (ft_strdup(str));
}

char	*get_pointer(unsigned long pntr, int *size)
{
	char	*str;
	char	*temp;

	if (pntr == 0)
	{
		*size += 5;
		return (ft_strdup("(nil)"));
	}
	temp = ft_itoa_hex(pntr, HEXA_VAL_MIN);
	str = ft_strjoin("0x", temp);
	*size += ft_strlen(str);
	return (free(temp), str);
}

char	*get_int(int nbr, int *size)
{
	char	*str;

	str = ft_itoa(nbr);
	*size += ft_strlen(str);
	return (str);
}

char	*get_unsigned_int(unsigned int nbr, int *size)
{
	char	*str;

	str = ft_itoa_u(nbr);
	*size += ft_strlen(str);
	return (str);
}
