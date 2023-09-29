/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_2d_array_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:13:08 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_2d_array_struct(void ***array, void (*clean_data)(void *))
{
	const unsigned long int	size = sizeof(array);
	unsigned long int		i;

	i = 0;
	if (!*array)
		return ;
	while (i < size)
	{
		if (*array || *array[i])
			clean_data(*array[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
