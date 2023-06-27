/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:32:52 by marine            #+#    #+#             */
/*   Updated: 2023/02/08 01:15:21 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_powten(int i)
{
	int	j;
	int	n;

	j = 0;
	n = 1;
	while (j < i)
	{
		n *= 10;
		j++;
	}
	return (n);
}

static int	ft_nblen(int i)
{
	int	j;

	j = 0;
	if (i == 0)
		return (1);
	while (i)
	{
		i = i / 10;
		j++;
	}
	return (j);
}

static int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*number;
	int		j;
	int		neg;

	neg = 0;
	if (n < 0)
		neg = 1;
	i = 0;
	j = ft_nblen(n) - 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	number = ft_calloc((ft_nblen(n) + 1 + neg), sizeof(char));
	if (number == NULL)
		return (NULL);
	if (n == 0)
		number[i] = '0';
	if (n < 0)
		number[i++] = '-';
	while (j + neg >= neg)
	{
		number[i] = (absolute(n) / ft_powten(j)) + 48;
		n = absolute(n) - (ft_powten(j--) * (number[i++] - 48));
	}
	return (number);
}
