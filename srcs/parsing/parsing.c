/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 14:53:26 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data, t_info *info)
{
	if (!check_syntax(data->input))
			return (SYNTAX_ERROR);
	else
	{	
		ft_split_space(data->input, info); //lexer, attention, on va avoir une verif a faire
		display_lexer(info);
		parser(info); //lexer, attention, on va avoir une verif a faire
	}
	return (FUNCTION_SUCCESS);
}
