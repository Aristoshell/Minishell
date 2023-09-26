/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:36:40 by madavid           #+#    #+#             */
/*   Updated: 2023/09/26 21:18:05 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// single quote, pas d'expand
// double quote, expand

bool	word_has_expand(const char *token_val)
{
	int		i;

	i = 0;
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
		else if (ft_is_dollar(token_val[i]))
			return (true);
		i++;
	}
	return (false);
}


int	count_exp_input_size(const char *input)
{
	int		i;
	int		count;
	char	quote;
	
	quote = 0;
	while (input[i])
	{
		if (ft_is_simple_quote(input[i]))
		{
			i++;
			count++;
			while (input[i] && input[i] != '\'')
			{
				i++;
				count++;
			}
		}
		else
		{
			if (ft_is_dollar(input[i]))
			{
				//get_key; pour avoir le nom
				//tant que 
				
			}
		}
	}
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
