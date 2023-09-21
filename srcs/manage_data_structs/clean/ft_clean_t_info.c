/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 18:10:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*peut etre quil faut un **info pour bien le clean ?*/

void	ft_free_t_info(t_info *info)
{
	info->nb_tokens = 0;
	*info->current_word = 0;
	ft_clean_2d_array(info->tokens, ft_clean_t_tokens);
}
