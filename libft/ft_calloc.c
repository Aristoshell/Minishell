/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:36:20 by lmarchai          #+#    #+#             */
/*   Updated: 2022/11/23 16:07:23 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	new = malloc(nmemb * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}
