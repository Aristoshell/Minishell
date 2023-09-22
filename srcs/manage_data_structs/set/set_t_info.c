/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_t_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/23 01:43:37 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_info(t_info *info)
{
	info->nb_tokens = 0;
	info->current_word = 0;
}
void	ft_reinit_info(t_info *info)
{
	ft_init_info(info);
	if (info->tokens)
	{
		printf("TEST\n");
		ft_clean_2d_array_struct((void ***)&info->tokens, (void *)ft_clean_t_token);
	}
}


t_info	*create_info(t_info *info)
{
	info = malloc(sizeof(t_info));
	if (!info)
		return (MEMORY_ERROR_PT); // la il faudra supprimer data
	ft_init_info(info);
	return (info);
}
