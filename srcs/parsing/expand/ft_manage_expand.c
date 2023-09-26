/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:36:40 by madavid           #+#    #+#             */
/*   Updated: 2023/09/26 17:44:54 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// single quote, pas d'expand
// double quote, expand

bool	word_has_expand(const char *token_val, t_envlist *env)
{
	int		i;

	i = 0;
	(void) env;
	while (token_val[i])
	{
		if (ft_is_simple_quote(token_val[i]))
		{
			i++;
			while (token_val[i] && token_val[i] != '\'')
				i++;
		}
		else if (ft_is_double_quote(token_val[i]))
		{
			i++;
			while (token_val[i] && token_val[i] != '"')
			{
				if (ft_is_dollar(token_val[i]))
					return (true);
				i++;
			}
		}	
		else
		{
			if (ft_is_dollar(token_val[i]))
				return (true);
		}
		i++;
	}
	return (false);
}

// void	ft_manage_expand(t_info *info, t_envlist *env)
// {
// 	int				i;
// 	t_token_type	type;

// 	i = 0;
// 	while (i < info->nb_tokens)
// 	{
// 		type = info->tokens[i]->type;
// 		if (type == type_word)
// 		{
// 			//checker si expand
// 		}
// 		i++;
// 	}
	
// }
