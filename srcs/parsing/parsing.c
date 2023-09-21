/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 20:27:05 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data, t_info *info)
{
	int	function_return;

	if (!check_syntax(data->input))
			return (SYNTAX_ERROR);
	else
	{	
		function_return = lexer(data->input, info);
		if (function_return != FUNCTION_SUCCESS)
			return (ft_error(function_return, data, info));
		display_lexer(info);
		//function_return = parser(info); // attention, on va avoir une verif a faire
		//if (function_return != FUNCTION_SUCCESS)
		//	return (ft_error(function_return, data, info));
	}
	return (FUNCTION_SUCCESS);
}

