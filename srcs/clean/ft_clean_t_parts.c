/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_parts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:34:37 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_t_parts(t_parts *part)
{
	ft_clean_string(part->string);
	part->token = token_default;
}
