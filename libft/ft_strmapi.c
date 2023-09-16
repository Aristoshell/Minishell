/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:46:50 by lmarchai          #+#    #+#             */
/*   Updated: 2022/12/07 23:11:12 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	size_t	i;
	char	*final;

	i = 0;
	final = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!final)
		return (NULL);
	while (i < ft_strlen(s))
	{
		final[i] = f(i, (char)s[i]);
		i++;
	}
	final[i] = '\0';
	return (final);
}
