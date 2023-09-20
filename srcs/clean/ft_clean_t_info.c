/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:34:44 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_t_info(t_info *info)
{
	info->nb_words = 0;
	*info->current_word = 0;
	ft_clean_2d_array(info->words, ft_clean_t_parts);
}
