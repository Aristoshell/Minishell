/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:37:52 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 13:37:53 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	len_dst;

	if (n == 0 || n <= ft_strlen(dst))
		return (ft_strlen(src) + n);
	i = 0;
	len_dst = ft_strlen(dst);
	while (src[i] && (i + len_dst) < (n - 1))
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + ft_strlen(src));
}

// int	main(int argc,	char **argv)
// {
// 	int	result;

// 	result = ft_strlcat(argv[1], argv[2], ft_atoi(argv[3]));
// 	if (argc != 4)
// 		return (0);
// 	else
// 		printf("%d\n", result);
// }
