/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 13:29:44 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_info *info)
{
	info->nb_words = -1;
	info->(*current_word) = 0;
	info->words = NULL;
}

t_info	*create_info(t_info *info)
{
	info = malloc(sizeof(t_data));
	if (!info)
		return (MEMORY_ERROR_PT); // la il faudra supprimer data
	init_info(info);
	return (info);
}
