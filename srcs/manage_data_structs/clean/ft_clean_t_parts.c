/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_parts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 18:13:55 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_t_tokens(t_tokens *token)
{
	if (!token)
		return ;
	ft_clean_string(token->string);
	token->type = type_default;
}


/*

de mon ancien code

void	delete_t_tokens(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_tokens)
	{
		if (info->tokens[i])
			free(info->tokens[i]);
		i++;
	}
	info->nb_tokens = 0;
	info->tokens = NULL;
}

*/