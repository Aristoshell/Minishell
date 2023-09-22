/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_tokem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/22 17:28:30 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_t_token(t_token *token)
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