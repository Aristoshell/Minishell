/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two_di_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:42:10 by madavid           #+#    #+#             */
/*   Updated: 2023/09/19 17:58:40 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_array(char **two_di_array)
{
	int	i;

	i = 0;
	while (two_di_array[i])
	{
		ft_bzero(two_di_array[i], ft_strlen(two_di_array[i]));
		free(two_di_array[i]);
		i++;
	}
	free (two_di_array);
}

void	ft

void	ft_free_2d_data_array(void **data, void (*f)(void *), int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		f(data[i]);
		i++;
	}
	free (data);
}


/*
Ici je veux creer une fonction qui va me permettre de free des tableau de structs

- je lui envoi le type de structure, la fonction a appeler puis la taille du tableau 
- la fonction va iterer sur la stucture
*/