/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_t_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 18:10:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_info *info)
{
	info->nb_tokens = -1;
	info->(*current_word) = 0;
	info->tokens = NULL;
}

t_info	*create_info(t_info *info)
{
	info = malloc(sizeof(t_data));
	if (!info)
		return (MEMORY_ERROR_PT); // la il faudra supprimer data
	init_info(info);
	return (info);
}
