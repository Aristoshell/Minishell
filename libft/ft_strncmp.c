/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:31:23 by lmarchai            #+#    #+#           */
/*   Updated: 2022/08/25 16:31:23 by lmarchai           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t nb)
{
	size_t	i;

	i = 0;
	if (nb <= 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < nb -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
