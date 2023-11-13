/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:35:08 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 05:14:18 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{	
		c += 32;
		return (c);
	}
	else
		return (c);
}
