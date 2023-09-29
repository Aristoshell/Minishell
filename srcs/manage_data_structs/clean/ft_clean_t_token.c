/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/23 01:39:38 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_t_token(t_token **token)
{
	if (!token || !*token || !(*token)->string)
		return ;
    ft_clean_string(&((*token)->string));
	//token->type = type_default; //enleve car bug
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