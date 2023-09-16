/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:12:56 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/07 12:12:56 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_char(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*final;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	final = malloc((calc_char(n) + neg + 1) * sizeof(char));
	if (!final)
		return (NULL);
	final[calc_char(n) + neg] = '\0';
	if (neg == 1)
		final[0] = '-';
	while (n > 9)
	{
		final[calc_char(n) + neg - 1] = n % 10 + '0';
		n = n / 10;
	}
	final[neg] = n + '0';
	return (final);
}
