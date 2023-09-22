/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_2d_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:13:08 by madavid           #+#    #+#             */
/*   Updated: 2023/09/22 19:15:32 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_2d_array(void **array, void (*clean_data)(void *))
{
	const unsigned long int	size = sizeof(array);
	unsigned long int		i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
	{
		if (array[i])
			clean_data(&array[i]);
		i++;
	}
	free(array);
}