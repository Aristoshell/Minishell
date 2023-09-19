/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/19 17:45:06 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// il faut pas carrement free t_info ** ?
void	ft_free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_words)
	{		
 		ft_bzero(info->words[i]->string, ft_strlen(info->words[i]->string));
		if (info->words[i]->string)
			free(info->words[i]->string);
		info->words[i]->string = NULL;
		i++;
	}
	if (info->nb_words > 0)
		free(info->words);
	info->nb_words = -1;
}

void	ft_free_data(t_data *data)
{
	
}